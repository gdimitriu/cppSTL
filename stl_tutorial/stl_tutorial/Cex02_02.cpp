#include "StdAfx.h"
#include "Cex02_02.h"
#include <cassert>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename container> container Make(const char str[])
{
	return container(&str[0],&str[strlen(str)]);
}

Cex02_02::Cex02_02(void)
{
}


Cex02_02::~Cex02_02(void)
{
}


void Cex02_02::run(void)
{
	cout<<"Using reverse algorithm with a vector\n";
	vector<char> vector1=Make<vector<char>>("mark twain");
	reverse(vector1.begin(),vector1.end());
	assert(Make<vector<char>>("niawt kram")==vector1);
	cout<<"---- OK ----"<<endl;
	cout<<"Using reverse algorithm with a list\n";
	list<char> list1=Make<list<char>>("mark twain");
	reverse(list1.begin(),list1.end());
	assert(Make<list<char>>("niawt kram")==list1);
	cout<<"---- OK ----"<<endl;
	cout<<"Using reverse algorithm with a deque\n";
	deque<char> deque1=Make<deque<char>>("mark twain");
	reverse(deque1.begin(),deque1.end());
	assert(Make<deque<char>>("niawt kram")==deque1);
	cout<<"---- OK ----"<<endl;

}
