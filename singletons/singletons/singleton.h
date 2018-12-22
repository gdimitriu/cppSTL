#include <iostream>
#include <string>
using namespace std;
class Singleton;
class Singleton
{
public:
	static Singleton* Instance()
	{
		if (!pInstance_)
		{
		// Check for dead reference
			if (destroyed_)
			{
				OnDeadReference();
			}
			else
			{
				// First call—initialize
				Create();
			}
		}
		return pInstance_;
	}
	int DoSomething()
	{
		std::cout<<strSingleton;
		return strSingleton.max_size();
	};
private:
	// Create a new Singleton and store a
	// pointer to it in pInstance_
	static void Create()
	{
		// Task: initialize pInstance_
		static Singleton theInstance;
		pInstance_ = &theInstance;
	}
	// Gets called if dead reference detected
	static void OnDeadReference();
	virtual ~Singleton()
	{
		std::cout<<"called destructor\n";
		pInstance_ = 0;
		destroyed_ = true;
	}
	// Data
	static Singleton* pInstance_;
	static bool destroyed_;
	static string strSingleton;
	Singleton(){};
	Singleton(const Singleton* singleton){};
	Singleton& operator=(const Singleton&){return *this;};
	static void KillPhoenixSingleton(); // Added
};


namespace Private
{
	class LifetimeTracker
	{
	public:
		LifetimeTracker(unsigned int x) : longevity_(x) {}
		virtual ~LifetimeTracker() = 0;
		friend inline bool Compare( unsigned int longevity, const LifetimeTracker* p)
		{
			return p->longevity_ > longevity;
		}
	private:
		unsigned int longevity_;
	};
	// Definition required
	inline LifetimeTracker::~LifetimeTracker() {}
	
	typedef LifetimeTracker** TrackerArray;
	extern TrackerArray pTrackerArray;
	extern unsigned int elements;

	//Helper destroyer function
	template <typename T>
	struct Deleter
	{
		static void Delete(T* pObj)
		{
			delete pObj;
		}
	};
	// Concrete lifetime tracker for objects of type T
	template <typename T, typename Destroyer>
	class ConcreteLifetimeTracker : public LifetimeTracker
	{
	public:
		ConcreteLifetimeTracker(T* p,unsigned int longevity,Destroyer d) :LifetimeTracker(longevity),pTracked_(p),destroyer_(d)
		{}
		~ConcreteLifetimeTracker()
		{
			destroyer_(pTracked_);
		}
	private:
		T* pTracked_;
		Destroyer destroyer_;
	};
	void AtExitFn(); // Declaration needed below

	template <typename T, typename Destroyer>
	void SetLongevity(T* pDynObject, unsigned int longevity,Destroyer d = Private::Deleter<T>::Delete)
	{
		TrackerArray pNewArray = static_cast<TrackerArray>(std::realloc(pTrackerArray, sizeof(T) * (elements + 1)));
		if (!pNewArray) throw std::bad_alloc();
		pTrackerArray = pNewArray;
		LifetimeTracker* p = new ConcreteLifetimeTracker<T, Destroyer>(pDynObject, longevity, d);
		TrackerArray pos = std::upper_bound(pTrackerArray, pTrackerArray + elements, longevity, Compare);
		std::copy_backward(pos, pTrackerArray + elements,pTrackerArray + elements + 1);
		*pos = p;
		++elements;
		std::atexit(AtExitFn);
	}
}