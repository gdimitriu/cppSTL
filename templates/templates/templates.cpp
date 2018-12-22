// templates.cpp : Defines the entry point for the console application.
//
//http://www.cplusplus.com/reference/type_traits/
#include "stdafx.h"
#include "typelists.h"
using namespace TL;

template<typename t1,typename t2>
class normal
{
public:
	normal(t1 x,t2 y): x_(x),y_(y)
	{

	}
	normal(){};
	~normal(){};
	t1 x_;
	t2 y_;
};

class base
{
public:
	base(){};
	virtual ~base(){};
	int a;
};

template<class t1,template<class> class t2>
class derivata : public t2<t1>
{
public:
	derivata(){}
	~derivata(){}
};

template<class T>
struct handler
{
	T *value;
};


template<int i,typename t1,typename t2,template<typename,class> class t3>
void function(t3<t1,t2> obj)
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	normal<int,long> bla;
	function<0>(bla);
	derivata<long,handler> bla1;
	function<0>(bla1);
	return 0;
}

