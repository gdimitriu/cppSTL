#include "gadiList.h"
#include <cassert>
#include <list>
#include <iterator>
#include <iostream>
#include <ostream>

using namespace std;
/*
class verify;
class tester {
    friend verify;
    static int livecount;
    const tester* self;
public:
    tester() :self(this) {++livecount;}
    tester(const tester&) :self(this) {++livecount;}
    ~tester() {assert(self==this);--livecount;}
    tester& operator=(const tester& b) {
        assert(self==this && b.self == &b);
        return *this;
    }
    void cfunction() const {assert(self==this);}
    void mfunction() {assert(self==this);}
};
class verify {
public:
    ~verify() {assert(tester::livecount==0);}
}varifier;
*/
int main(void)
{
	list<int> _list;
	gadiList<int> gadi;
	gadiList<int> gadi1;
	for(int i=0;i<10;++i)
		_list.push_back(i);
	for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
	{
		gadi.push_back(*i);
	}
	for(gadiList<int>::iterator i=gadi.begin();i!=gadi.end();++i)
	{
		cout<<*i<<" ";
	}
	cout<<endl;
	ostream_iterator<int> output_it(cout," ");
	copy(gadi.begin(),gadi.end(),output_it);
	cout<<endl;

	for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
	{
		gadi1.push_front(*i);
	}
	for(gadiList<int>::iterator i=gadi1.begin();i!=gadi1.end();++i)
	{
		cout<<*i<<" ";
	}
	cout<<endl;
	copy(gadi1.begin(),gadi1.end(),output_it);
	cout<<endl;
	cout<<gadi.front()<<" "<<gadi.back()<<endl;
	cout<<gadi1.front()<<" "<<gadi1.back()<<endl;
	gadiList<int>::iterator iter=gadi.begin();
	for(int i=0;i<5;++i)
	{
		iter=gadi.erase(iter);
	}
	iter=gadi1.begin();
	for(int i=0;i<5;++i)
	{
		iter=gadi1.erase(iter);
	}
	cout<<endl;
	copy(gadi.begin(),gadi.end(),output_it);
	cout<<endl;
	copy(gadi1.begin(),gadi1.end(),output_it);
	cout<<endl;
	exit(0);
}