#include "StdAfx.h"
#include "Cstd_libs.h"
#include <iostream>
#include <string>

Cstd_libs::Cstd_libs(void)
{
}


Cstd_libs::~Cstd_libs(void)
{
}


void Cstd_libs::run_inout(void)
{
	std::string str;
	std::cout<<"with normal spacing\n";
	std::cout<<"Please input your name\n";
	std::getline(std::cin,str);
	if(str==std::string("")||str==std::string("\n"))
	{
		str.clear();
		std::getline(std::cin,str);
	}
	std::cout<<"Hello, "<<str<<" !\n";
	std::cout<<"without spacing\n";
	str.clear();	
	std::cout<<"Please input your name\n";
	std::cin>>str;
	std::cout<<"Hello, "<<str<<" !\n";	
}
