#include "StdAfx.h"
#include "Citerators.h"
#include <iostream>
#include <iterator>
#include <cassert>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
#include <map>

template <typename container,typename T> container Citerators::make(const T str[])
{
	return container(&str[0],&str[strlen(str)]);
}
Citerators::Citerators(void)
{
}


Citerators::~Citerators(void)
{
}


void Citerators::run(void)
{
	if(0)
	{
		ex04_01();
		iterators_wo_examples();
		istream_ex();
		ostream_ex();
		iostream_ex();
		setmap_ex();
	}
}


void Citerators::ex04_01(void)
{
	//initialize the array a with 10 integers
	int a[10]={12,3,25,7,11,213,7,123,29,-31};
	//find the first element equat to 7 in the array
	int *ptr=std::find(&a[0],&a[10],7);
	assert(7==*ptr && 11==*(ptr+1));
	//initialize list1 with the same integers as in array a
	std::list<int> list1(&a[0],&a[10]);
	//find the element 7
	std::list<int>::iterator i=std::find(list1.begin(),list1.end(),7);
	assert(7==*i && 11==*(++i));
	std::cout<<"Type some characters, inclunding an 'x' followed \n"
		<<"by a least one nonwhite-space character: "<<std::flush;
	std::istream_iterator<char> in(std::cin);
	std::istream_iterator<char> eos;
	std::find(in,eos,'x');
	std::cout<< "The first nonwhite-space character following \n"
		<<"the first 'x' was '"<<*(++in)<<"'."<<std::endl;
}


void Citerators::iterators_wo_examples(void)
{
	//initialize the array with 10 integers
	int a[10]={1,2,3,4,5,1,2,3,4,5};
	//create the list
	std::list<int> list1;
	//create the iterator class
	std::back_insert_iterator<std::list<int>> back_insert_it(list1);
	std::copy(&a[0],&a[5],back_insert_it);
	//test for the result
	assert(list1==std::list<int>(&a[0],&a[5]));
	std::cout<<"------OK with class created before\n";
	//clear the list
	list1.clear();
	std::copy(&a[0],&a[5],std::back_insert_iterator<std::list<int>>(list1));
	//test for the result
	assert(list1==std::list<int>(&a[0],&a[5]));
	std::cout<<"------OK with one time class\n";
	//clear the list
	list1.clear();
	std::copy(&a[0],&a[5],std::back_inserter(list1));
	//test for the result
	assert(list1==std::list<int>(&a[0],&a[5]));
	std::cout<<"------OK with back inserter\n";
	//clear the list
	list1.clear();
	//copy at back of the list
	std::copy(&a[0],&a[5],std::back_inserter(list1));
	//copy at the front of the list (so in reverse order)
	std::copy(&a[0],&a[5],std::front_inserter(list1));
	//initialize the new array for rezult
	int rez[10];
	std::copy(&a[0],&a[10],&rez[0]);
	//reverse the push front part
	std::reverse(&rez[0],&rez[5]);
	//test for the result
	assert(list1==std::list<int>(&rez[0],&rez[10]));
	std::cout<<"------OK with front and back inserter\n";
	//clear the list
	list1.clear();
	//initialize the input data
	int b[10]={1,2,3,4,5,6,7,8,9,10};
	//copy at the back of the list
	std::copy(&b[0],&b[5],std::back_inserter(list1));
	std::copy(&b[5],&b[10],std::inserter(list1,list1.begin()));
	//intialize the result
	int rez1[10]={6,7,8,9,10,1,2,3,4,5};
	assert(list1==std::list<int>(&rez1[0],&rez1[10]));
	std::cout<<"------OK with back inserter and inserter\n";
}


void Citerators::istream_ex(void)
{
	//initialize the array with 5 values
	int a[5]={1,2,3,4,5};
	std::cout<<"Input 5 int values folowed by a character: "<<std::endl;
	//create the vector with the values from array
	std::vector<int> vect1(&a[0],&a[5]);
	//declare the list that will store the data
	std::list<int> list1;
	//merge the input stream and the vector
	std::merge(vect1.begin(),vect1.end(),std::istream_iterator<int>(std::cin),std::istream_iterator<int>(),std::back_inserter(list1));
	//print the resulted merged
	std::cout<<"merged values with the a vector is:\n";
	for(std::list<int>::iterator i=list1.begin();i!=list1.end();++i)
	{
		std::cout<<*i<<" ";
	}
}


void Citerators::ostream_ex(void)
{
	//initialize the array with 5 values
	int a[5]={1,2,3,4,5};
	//create a vector from the array
	std::vector<int> vect1(&a[0],&a[5]);
	//declare a new array because merge works only with sorted structures
	int b[5]={6,7,8,9,10};
	//merge the two structures and output them
	std::merge(vect1.begin(),vect1.end(),&b[0],&b[5],std::ostream_iterator<int>(std::cout," "));
}


void Citerators::iostream_ex(void)
{
	//initialize the array with 5 values
	int a[5]={1,2,3,4,5};
	std::cout<<"Please input some integers followed by a character: "<<std::endl;
	//merge the array with the input data to the output stream
	//notice that the input/output is done in parallel first you input the data and then the print is done
	std::merge(&a[0],&a[5],std::istream_iterator<int>(std::cin),std::istream_iterator<int>(),std::ostream_iterator<int>(std::cout," "));
}


void Citerators::setmap_ex(void)
{
	//this is a set and map example
	std::set<int> setinstance;
	//populate the set
	setinstance.insert(3);
	setinstance.insert(5);
	setinstance.insert(7);
	//get the iterator to the first element
	std::set<int>::iterator i=setinstance.begin();
	//insert instead of 3 the 4
	setinstance.erase(i);
	setinstance.insert(4);

	//working with maps
	typedef std::multimap<int,double> multimap_1;
	multimap_1 m;
	//insert a value
	m.insert(std::pair<const int,double>(3,4.1));
	multimap_1::iterator imap=m.begin();
	//this is how should not do it
	//*i=std::pair<const int,double>(3,5.1));
	//this should be the faster way to do it
	imap->second=5.1;
	//this is by the book way to do it
	m.erase(imap);
	m.insert(std::pair<const int,double>(3,5.1));
}
