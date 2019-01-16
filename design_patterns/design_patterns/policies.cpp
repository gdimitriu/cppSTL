#include<iostream>
//class for opnew

template<typename T> struct NewOperator
{
	static T* Create()
	{
		return new T;
	}
protected:
	~NewOperator(){};
};

template<typename T> struct MallocCreator
{
	static T* Create()
	{
		void * buff_=std::malloc(sizeof(T));
		if(!buff_) return 0;
		return new(buff_) T;
	}
protected:
	~MallocCreator(){};
};

template <typename T>
struct PrototypeCreator
{
	PrototypeCreator(T *pObj=0):pPrototype_(pObj)
	{
	}
	T* Create()
	{
		return pPrototype_ ? pPrototype_->Clone() : 0;
	}
	T* GetPrototype() { return pPrototype_;}
	void SetPrototype(T* pObj) { pPrototype_=pObj;}
private:
	T* pPrototype_;
protected:
	~PrototypeCreator(){delete pPrototype_;};
};

class CUse
{
private:
	int m_iValue;
public:
	CUse(){m_iValue=0; std::cout<<"use constructor\n";}
	void DoSomething() { m_iValue++;std::cout<<"m_iValue="<<m_iValue<<std::endl;}
	CUse *Clone(void) { return new CUse(*this);};
};

template <template <class created> class CreationPolicy> class CUseManager : public CreationPolicy<CUse>
{
public:
	void DoSomething(void)
	{
		CUse* a=CreationPolicy<CUse>::Create();
		a->DoSomething();
		delete a;
	}
	void SwitchPrototype(CUse *pNewPrototype)
	{
		CreationPolicy<CUse>& myPolicy=*this;
		delete myPolicy.GetPrototype();
		myPolicy.SetPrototype(pNewPrototype);
	}
};

typedef CUseManager<MallocCreator> mallocUse;
typedef CUseManager<PrototypeCreator> prototypeUse;
int main(void)
{
	std::cout<<"before constructor"<<std::endl;

	mallocUse bla_;
	bla_.DoSomething();

	prototypeUse *proto_=new prototypeUse;
	
	CUse* tmp_=new CUse;
	proto_->SetPrototype(tmp_);

	CUse *f=proto_->Create();
	f->DoSomething();
	f->DoSomething();
	CUse *f1=proto_->Create();
	f1->DoSomething();
	proto_->SwitchPrototype(f);
	delete f1;
	f1=proto_->Create();
	f1->DoSomething();

	delete proto_;
	//dubious
//	MallocCreator<CUse>* pDubios=&bla_;
//	delete pDubios;
//	bla_.SwitchPrototype(f);
	//final wait
	getchar();
}
