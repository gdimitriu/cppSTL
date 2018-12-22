#pragma once

class BaseVisitor
{
public:
	virtual ~BaseVisitor(){}
};

template<class T,typename R=void>
class Visitor
{
public:
	typedef R ReturnType;
	virtual ReturnType Visit(T&)=0;
};

// Visitable part
template <typename R = void>
class BaseVisitable
{
public:
	typedef R ReturnType;
	virtual ~BaseVisitable() {}
	virtual R Accept(BaseVisitor&) = 0;
protected:
	template <class T>
	static ReturnType AcceptImpl(T& visited, BaseVisitor& guest)
	{
	// Apply the Acyclic Visitor
		if (Visitor<T>* p =dynamic_cast<Visitor<T>*>(&guest))
		{
			return p->Visit(visited);
		}
		return ReturnType();
	}
};
#define DEFINE_VISITABLE() \
virtual ReturnType Accept(BaseVisitor& guest) \
{ return AcceptImpl(*this, guest); }