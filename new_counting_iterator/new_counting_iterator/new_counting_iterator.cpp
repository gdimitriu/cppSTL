// new_counting_iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>
//<define/include counting iterator class>
#include "counting_iterator.h"
using std::string;



int _tmain(int argc, _TCHAR* argv[])
{
	std::cout<<"Demonstrating a counting iterator class."<<std::endl;
	int x[]={12,4,3,7,17,9,11,6};
	counting_iterator<int*> i(&x[0],"Curly"),j(&x[0],"Moe"),end(&x[8],"Lary");
	std::cout<<"Traversing array x\n"
		<<" from i (Curly) to end (Larry)\n";
	while(i!=end)
	{
		std::cout<<*i<<std::endl;
		++i;
	}
	std::cout<<"After the transversal:\n";
	i.report(std::cout);
	end.report(std::cout);
	std::cout<<"Assigning j (Moe) to i (Curly)."<<std::endl;
	i=j;
	std::cout<<"Searching the array\n"
		<<" from i(Moe) to end (Larray)\n"
		<<" using find\n";
	counting_iterator<int *> k=std::find(i,end,9);
	std::cout<<"After the find:\n";
	k.report(std::cout);
	i.report(std::cout);
	end.report(std::cout);
	return 0;
}

