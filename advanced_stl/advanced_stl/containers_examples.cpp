#include "stdafx.h"
#include <iostream>
#include <list>
#include <algorithm>

class operation
{
public:
	void operator() (char val)
	{
		std::cout<<val<<' ';
	}
};

void test_list(void)
{
	operation op;
	std::list<char> coll;
	for(char c='a'; c<='z';++c)
		coll.push_back(c);
/*	std::list<char>::const_iterator pos;
	for(pos=coll.begin();pos!=coll.end();++pos)
		std::cout<<*pos<<' ';
*/
	std::for_each(coll.begin(),coll.end(),op);
	std::cout<<std::endl;
}