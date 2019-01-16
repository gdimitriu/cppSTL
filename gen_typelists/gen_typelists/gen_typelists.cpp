// gen_typelists.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
//#include "GeneratorHierarchy.h"
#include "typelists.h"
#include<string>
#include <iostream>
using namespace TL;
template <class T>
struct Holder
{
T value_;
};
//typedef GenScatterHierarchy<TYPELIST_3(int, long, std::string),Holder> WidgetInfo;
typedef TYPELIST_2(int,double) intd;
template<typename v>
struct blabla
{
	v blab;
};

blabla<intd> er;
int _tmain(int argc, _TCHAR* argv[])
{
	
	intd bala;
	std::cout<<"blblbk";
	//typedefs
	//	typedef TypeList<int,NullType> OneTypeOnly;
	typedef TYPELIST_1(int) OneTypeOnly;
//	typedef TypeList<char,TypeList<signed char,TypeList<unsigned char,NullType> > > AllCharTypes;
	typedef TYPELIST_3(char,signed char,unsigned char) AllCharTypes;
//	typedef TypeList<signed char, TypeList<short int,TypeList<int,TypeList<long int,NullType> > > > SingnedIntegrals;
	typedef TYPELIST_4(signed char,short int,int,long int) SignedIntegrals;
	typedef Append<NullType,char>::Result bla0;
	typedef Append<bla0,double>::Result bla1;
	typedef Append<SignedIntegrals, TYPELIST_3(float, double, long double) >::Result SignedTypes;
	typedef Erase<SignedTypes,double>::Result bla2;
/*
	WidgetInfo obj;
	(static_cast<Holder<long>&>(obj)).value_=12345;
	(static_cast<Holder<std::string>&>(obj)).value_="bla bla";
	std::cout<<(static_cast<Holder<std::string>&>(obj)).value_<<std::endl;
	std::cout<<(static_cast<Holder<long>&>(obj)).value_<<std::endl;
//	std::cout<<Field<std::string>(obj).value_<<std::endl;
//	std::cout<<Field<long>(obj).value_<<std::endl;
//	std::string value=Field<2>(obj).value_;
	std::cout<<value<<std::endl;
	std::cout<<Field<1>(obj).value_<<std::endl; */
	return 0;
}

