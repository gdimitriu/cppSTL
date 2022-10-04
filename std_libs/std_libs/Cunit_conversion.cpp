#include "StdAfx.h"
#include <iostream>
#include "Cunit_conversion.h"


Cunit_conversion::Cunit_conversion(void)
{
}


Cunit_conversion::~Cunit_conversion(void)
{
}


void Cunit_conversion::run(void)
{
	const float factor=2.54;
	float x,in,cm;
	char ch=0;
	std::cout<<"enter length: ";
	std::cin>>x; //read a floating point number
	std::cin>>ch; //read the sufix
	switch(ch) {
	case 'i': //inch
		in=x;
		cm=x*factor;
		break;
	case 'c': //cm
		in=x/factor;
		cm=x;
		break;
	default:
		in=cm=9;
		break;
	}
	std::cout<<in<<" in="<<cm<<"cm\n";
}
