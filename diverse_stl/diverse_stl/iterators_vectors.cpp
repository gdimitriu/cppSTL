#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

void test_ri_vectors(void)
{
	int test_Value=1;
	vector<int> vect;
	vect.push_back(0);
	vect.push_back(1);
	vect.push_back(2);
	vect.push_back(3);
	vect.push_back(4);
	vect.push_back(5);
	vector<int> ref(vect);
	vector<int>::iterator it=find(ref.begin(),ref.end(),test_Value);
	ref.erase(it);
	vector<int>::reverse_iterator ri=find(vect.rbegin(),vect.rend(),test_Value);
	vect.erase((++ri).base());
	vector<int>::iterator itref=ref.begin();
	for(it=vect.begin();it!=vect.end();++it,++itref)
	{
		assert(*it==*itref);
	}
	cout<<"end testing remove"<<endl;
	it=find(ref.begin(),ref.end(),test_Value+1);
	ref.insert(it,test_Value);
	ri=find(vect.rbegin(),vect.rend(),test_Value+1);
	vect.insert((++ri).base(),test_Value); //this should not be ++ as is said into the book
	itref=ref.begin();
	for(it=vect.begin();it!=vect.end();++it,++itref)
	{
		assert(*it==*itref);
//		cout<<*it<<" vs "<<*itref<<endl;
	}
	cout<<"end testing insert"<<endl;
}