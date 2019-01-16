#include "stdafx.h"
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;
struct StringPtrLess: public binary_function<const string *,const string *,bool>
{
	bool operator()(const string *ps1,const string *ps2) const
	{
		return *ps1<*ps2;
	}
};
static void print(const string *ps)
{
	cout<<*ps<<endl;
};

struct Dereference {
	template <typename T> const T& operator()(const T *ptr) const
	{
		return *ptr;
	}
};

void test_sets(void)
{
	set<string*,StringPtrLess> ssp;
	ssp.insert(new string("Anteater"));
	ssp.insert(new string("Wombat"));
	ssp.insert(new string("Lemur"));
	ssp.insert(new string("Penguin"));

	//print all elements using for
	cout<<"Print all elements using for\n";
	for(set<string *,StringPtrLess>::iterator i=ssp.begin();i!=ssp.end();++i)
		cout<<**i<<endl;
	//print all elements using copy
//	cout<<"Print all elements using copy\n";
//	copy(ssp.begin(),ssp.end(),ostream_iterator<string *>(cout,"\n"));
	//print all elements using for_each and a function
	cout<<"Print all elements using for_each and a function\n";
	for_each(ssp.begin(),ssp.end(),print);
	cout<<"Print all elements using transform\n";
	transform(ssp.begin(),ssp.end(),ostream_iterator<string>(cout,"\n"),Dereference());
}