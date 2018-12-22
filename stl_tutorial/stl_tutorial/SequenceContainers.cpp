#include "StdAfx.h"
#include "SequenceContainers.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

using std::vector;

SequenceContainers::SequenceContainers(void)
{
}


SequenceContainers::~SequenceContainers(void)
{
}


void SequenceContainers::run(void)
{
	ex06_01();
}


void SequenceContainers::ex06_01(void)
{
	std::cout<<"Demonstrating simpliest vector constructions"<<std::endl;
	vector<char> vector1,vector2(3,'x');
	assert(0==vector1.size());
	assert(3==vector2.size());
	assert('x'==vector2[0] && 'x'==vector2[1] && 'x'==vector2[2]);
	assert(vector2==vector<char>(3,'x') && vector2!=vector<char>(4,'x'));
	std::cout<<"------OK."<<std::endl;
}

