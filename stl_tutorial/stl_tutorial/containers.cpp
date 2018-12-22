#include "StdAfx.h"
#include "containers.h"
#include <map>
#include <iostream>
#include <string>

containers::containers(void)
{
}


containers::~containers(void)
{
}


void containers::ex02_04(void)
{
	std::map<std::string,long> directory;
	directory["guta"]=12345;
	directory["gigi"]=23456;
	directory["gogu"]=34567;
	std::string name_tosearch;
	std::cout<<"please input a name\n";
	while(std::cin>>name_tosearch)
	{
		if(directory.find(name_tosearch)!=directory.end())
		{
			std::cout<<name_tosearch<<" has the telephone nr="<<directory[name_tosearch]<<std::endl;
			name_tosearch.clear();
			std::cout<<"please input a name\n";
		}
		else
		{
			std::cout<<"the person "<<name_tosearch<<" does not have any telephone nr here\n";
			return;
		}
	}
}
