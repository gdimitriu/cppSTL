#pragma once
#include<cassert>
#include<memory>
#include <algorithm>

//classical statical singleton
template<class T>
class singleton_static
{
public:
	static T& Instance()
	{
		static T obj;
		return obj;
	}
private:
	singleton_static(){};
	singleton_static(const singleton_static& singleton){};
	singleton_static & operator=(const singleton_static& singelton){};
	~singleton_static(){};
};

//phoenix singleton it will recreate the object if it was destroy
template<class T>
class singleton_phoenix : public T
{
public:
	static singleton_phoenix& Instance()
	{
		if(pInstance_==nullptr)
		{
			if(bDestroyed_)
				CreatePhoenix();
			else
				Create();
		}
		return *pInstance_;
	}
private:
	singleton_phoenix(){};
	singleton_phoenix(const singleton_phoenix& singleton){};
	singleton_phoenix& operator=(const singleton_phoenix& singleton){};
	~singleton_phoenix()
	{
		bDestroyed_=true;
		pInstance_=nullptr;
	};
	//here we actual create the class
	static void Create(void)
	{
		static singleton_phoenix theInstance;
		pInstance_=&theInstance;
	}
	static void CreatePhoenix(void)
	{
#ifdef _DEBUG
		std::cout<<"here is phoenix!!\n";
#endif
		Create(); //obtain the old reference
		//create the new object
		new(pInstance_) singleton_phoenix;
//		#ifdef ATEXIT_FIXED //don't ask why is not fixed on vc 2012
			atexit(KillPhoenix);
//		#endif
		bDestroyed_=false;
	}
	static void KillPhoenix(void)
	{
#ifdef _DEBUG
		std::cout<<"here we destroy it again!!\n";
#endif
		//destroy it again
		pInstance_->~singleton_phoenix();
	}
	static singleton_phoenix* pInstance_;
	static bool bDestroyed_;
};

//singletion with longevity

namespace Longevity
{
	//tracker for lifetime
	class LifetimeTracker
	{
	public:
		LifetimeTracker(unsigned int longevity) : iLongevity_(longevity) {}
		virtual ~LifetimeTracker()=0;
		//compare function used by priority queue algorithm
		friend inline bool Compare(unsigned int longevity,const LifetimeTracker* tracker)
		{
			return tracker->iLongevity_>longevity;
		}
	private:
		unsigned int iLongevity_;
	};
	//this definition is needed to have the pPriorityQueue
	inline LifetimeTracker::~LifetimeTracker(){};
	//this is the priority queue for the lifetime
	typedef LifetimeTracker** LifetimeTrackerArray;
	extern LifetimeTrackerArray pPriorityQueue;
	extern unsigned int iElements;
	//destroyer helper to delete an element this is used to have private destructor
	template<class T>
	struct DestroyerHelper
	{
		static void Delete(T* pobj)
		{
			delete pobj;
		}
	};
	//concrete template for lifetimetracker
	template<class T,typename Destroyer>
	class concreteLifetimeTracker : public LifetimeTracker
	{
	public:
		concreteLifetimeTracker(T *p,unsigned int lifetime,Destroyer d) : pTracker_(p),LifetimeTracker(lifetime),Destroyer_(d)
		{
		}
		~concreteLifetimeTracker()
		{
			 Destroyer_(pTracker_);
		}
		static void AtExitFn()
		{
			assert(iElements > 0 && pPriorityQueue != 0);
			// Pick the element at the top of the stack
			LifetimeTracker* pTop = pPriorityQueue[iElements - 1];
			// Destroy the element
			delete pTop;
			// Remove that object off the stack
			// Don't check errors-realloc with less memory can't fail
			pPriorityQueue = static_cast<LifetimeTrackerArray>(std::realloc(pPriorityQueue, sizeof(LifetimeTracker*) * --iElements));
		}
	private:
		T *pTracker_;
		Destroyer Destroyer_;
	};
};
//function to set the longevity of a singleton
template <typename T,typename Destroyer>
void SetLongevity(T* pDynObject, unsigned int longevity,Destroyer d)
{
	using namespace Longevity;
	LifetimeTrackerArray pNewArray = static_cast<LifetimeTrackerArray>(std::realloc(pPriorityQueue, sizeof(LifetimeTracker*) * (iElements + 1)));
	if (!pNewArray) throw std::bad_alloc();
	pPriorityQueue = pNewArray;
	LifetimeTracker* p = new concreteLifetimeTracker<T,Destroyer>(pDynObject, longevity,d);
	//this is in fact the priority queue
	LifetimeTrackerArray pos = std::upper_bound(pPriorityQueue, pPriorityQueue + iElements, longevity, Compare);
	std::copy_backward(pos, pPriorityQueue + iElements,pPriorityQueue + iElements + 1);
	*pos = p;
	++iElements;
	//this is used to free the memory at exit
	std::atexit(concreteLifetimeTracker<T,Destroyer>::AtExitFn);
}

// longevity singleton derived from the implementation using templates
template<class T>
class singleton_longevity : public T
{
public:
	static singleton_longevity& Instance(void)
	{
		if(pInstance_==nullptr)
			Create();
		return *pInstance_;
	}
private:
	static void Create(void)
	{
		pInstance_=new singleton_longevity;
		SetLongevity(pInstance_,iLongevity_,Longevity::DestroyerHelper<T>::Delete);
	}
	singleton_longevity(){};
	singleton_longevity(const singleton_longevity& singleton){};
	~singleton_longevity(){};
	singleton_longevity& operator=(const singleton_longevity& singleton){};
	static singleton_longevity *pInstance_;
	static unsigned int iLongevity_;
};