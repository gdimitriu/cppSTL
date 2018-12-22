#include <memory>
#include "typelists.h"
using namespace TL;
template <typename R, class TypeList>
class FunctorImpl;

template <typename R>
class FunctorImpl<R, NullType>
{
public:
	virtual R operator()() = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};
template <typename R, typename P1>
class FunctorImpl<R, TYPELIST_1(P1)>
{
public:
	virtual R operator()(P1) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};
template <typename R, typename P1, typename P2>
class FunctorImpl<R, TYPELIST_2(P1, P2)>
{
public:
	virtual R operator()(P1, P2) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template <class ParentFunctor, typename Fun>
class FunctorHandler : public FunctorImpl< typename ParentFunctor::ResultType,typename ParentFunctor::ParmList >
{
public:
	typedef typename ParentFunctor::ResultType ResultType;
	FunctorHandler(const Fun& fun) : fun_(fun) {}
	FunctorHandler* Clone() const { return new FunctorHandler(*this); }
	ResultType operator()()
	{
		return fun_();
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1)
	{
		return fun_(p1);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1,typename ParentFunctor::Parm2 p2)
	{
		return fun_(p1, p2);
	}
private:
	Fun fun_;
};

template <typename R, typename TList>
class Functor
{
private:
	// Handy type definition for the body type
	typedef FunctorImpl<R, TList> Impl;
	std::auto_ptr<Impl> spImpl_;
public:
	Functor(){};
	Functor(const Functor&){};
	Functor& operator=(const Functor&){};

	explicit Functor(std::auto_ptr<Impl> spImpl) : spImpl_(spImpl)
	{
	};
	
	typedef TList ParmList;
	typedef typename TypeAtNonStrict<TList, 0, NullType>::Result Parm1;
	typedef typename TypeAtNonStrict<TList, 1, NullType>::Result Parm2;
	typedef R ResultType;
	R operator()(Parm1 p1, Parm2 p2)
	{
		return (*spImpl_)(p1, p2);
	}
	R operator()()
	{
		return (*spImpl_)();
	}
	R operator()(Parm1 p1)
	{
		return (*spImpl_)(p1);
	}

	template <typename Fun>
	Functor(const Fun& fun) : spImpl_(new FunctorHandler<Functor, Fun>(fun))
	{
	}

};