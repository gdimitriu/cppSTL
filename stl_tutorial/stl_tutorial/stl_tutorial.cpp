// stl_tutorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Cpair_objects.h"
#include "Cex02_01.h"
#include "Cex02_02.h"
#include "containers.h"
#include "Cgeneric_algorithms.h"
#include "Citerators.h"
#include "SequenceContainers.h"

bool operator<(const Cpair<double,long> &x,const Cpair<double,long> &y)
{
	return x.first<y.first;
}
int _tmain(int argc, _TCHAR* argv[])
{
	if(0)
	{
		//old style C++
		Cpair_objects obj(123,'a');
		std::cout<<obj.first<<std::endl;
		std::cout<<obj.second<<std::endl;
		//template style
		Cpair<char,int> obj1('a',123);
		std::cout<<obj1.first<<std::endl;
		std::cout<<obj1.second<<std::endl;
		Cpair<bool,bool> obj_bools(true,false);
		std::cout<<obj_bools.first<<std::endl;
		std::cout<<obj_bools.second<<std::endl;

		//function template
		int u=3,v=5;
		double d=3.45,d1=4.67;
		std::cout<<max_template(u,v)<<"   "<<max_template(d,d1)<<std::endl;
		Cpair<double,long> first_double_0(3.45,999);
		Cpair<double,long> first_double_1(4.56,888);
		std::cout<<max_template(first_double_0,first_double_1).first<<std::endl;

		Cex02_01 reverseObj;
		reverseObj.run();
		Cex02_02 reversevect;
		reversevect.run();
		//containers
		containers container;
		//seraching containers
		container.ex02_04();
	}
	//generic algorithms
	Cgeneric_algorithms generic_alg;
	if(0)
	{
		generic_alg.runChapter2();
	}
	//iterators
	Citerators iterators;
	if(0)
	{
		iterators.run();
	}
	if(1)
	{
		generic_alg.runChapter5();
	}
	SequenceContainers seq;
	if(true)
	{
		seq.run();
	}
	return 0;
}

