#pragma once
#include "GeneratorHierarchy.h"

/* this is the abstract factory unit it has to be derived to use the correct creation policy*/
template <class T>
class AbstractFactoryUnit
{
public:
	virtual T* DoCreate(TL::Type2Type<T>) = 0;
	virtual ~AbstractFactoryUnit() {}
};

/* this is the abstract factory which derivate the Scatter Hierrarchy and it will use the AbstractFactoryUnit*/
/* It will have the base class for generation as templates arguments */
template <class TList,template <class> class Unit = AbstractFactoryUnit>
class AbstractFactory : public GenScatterHierarchy<TList, Unit>
{
public:
	typedef TList ProductList;
	template <class T> T* Create()
	{
		Unit <T>& unit = *this;
		return unit.DoCreate(TL::Type2Type<T>());
	}
};

/* this is in fact derivation of the AbstractFactoryUnit which implmented the new creation policy */
template <class ConcreteProduct, class Base>
class OpNewFactoryUnit : public Base
{
	typedef typename Base::ProductList BaseProductList;
protected:
	typedef typename BaseProductList::Tail ProductList;
public:
	typedef typename BaseProductList::Head AbstractProduct;
	ConcreteProduct* DoCreate(TL::Type2Type<AbstractProduct>)
	{
		return new ConcreteProduct;
	}
};

/* this is the Concrete Factory class which will generate the liniar hierarchy, it will inherit the GenLinearHierarchy */
template<class AbstractFact,template <class, class> class Creator = OPNewFactoryUnit, class TList = typename AbstractFact::ProductList>
class ConcreteFactory : public GenLinearHierarchy<typename TL::Reverse<TList>::Result, Creator, AbstractFact>
{
public:
	typedef typename AbstractFact::ProductList ProductList;
	typedef TList ConcreteProductList;
};

/* prototype factory unit this is equivalent with OpNewFactoryUnit */
/* this is using the prototype/cloning  paradingm */
template <class ConcreteProduct, class Base>
class PrototypeFactoryUnit : public Base
{
	typedef typename Base::ProductList BaseProductList;
protected:
	typedef typename BaseProductList::Tail ProductList;
public:
	typedef typename BaseProductList::Head AbstractProduct;
	PrototypeFactoryUnit(AbstractProduct* p = 0) :pPrototype_(p){}
	friend void DoGetPrototype(const PrototypeFactoryUnit& me, AbstractProduct*& pPrototype)
	{
		pPrototype = me.pPrototype_;
	}
	friend void DoSetPrototype(PrototypeFactoryUnit& me,AbstractProduct* pObj)
	{
		me.pPrototype_=pObj;
	}
	template <class U>
	void GetPrototype(AbstractProduct*& p)
	{
		return DoGetPrototype(*this, p);
	}
	template <class U>
	void SetPrototype(U* pObj)
	{
		DoSetPrototype(*this, pObj);
	}
	AbstractProduct* DoCreate(TL::Type2Type<AbstractProduct>)
	{
		assert(pPrototype_);
		return pPrototype_->Clone();
	}
	~PrototypeFactoryUnit()
	{
		delete pPrototype_;
	}
protected:
	AbstractProduct* pPrototype_;
};

/* Clone factory with a nullpointer check*/
template <class AbstractProduct, class Base>
class MyFactoryUnit : public PrototypeFactoryUnit<AbstractProduct, Base>
{
public:
	// Implement DoCreate so that it accepts a null prototype pointer
	AbstractProduct* DoCreate(TL::Type2Type<AbstractProduct>)
	{
		return pPrototype_ ? pPrototype_->Clone() : 0;
	}
};
