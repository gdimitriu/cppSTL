#include "StdAfx.h"
#include "Ccontainers.h"
#include <iterator>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

Ccontainers::Ccontainers(void)
{
}


Ccontainers::~Ccontainers(void)
{
}


void Ccontainers::string_oper(void)
{
	std::string m="Marry had a little lamb";
	std::cout<<m<<" had "<<count_wot(m,'a')<<" occurence of character a\n";
	std::cout<<m<<" had "<<count(m,'a')<<" occurence of character a with templates\n";
}

/*
	count the number of occurence of a character.
	this implementation is a standard implementation without templates.
*/
int Ccontainers::count_wot(const std::string &s, char c)
{
	std::string::const_iterator i=std::find(s.begin(),s.end(),c);
	int n=0;
	while(i!=s.end())
	{
		++n;
		i=std::find(i+1,s.end(),c);
	}
	return n;
}

/*
	count the number of occurence of a character
	this implementation is with templates
*/
template <class C,class T> int Ccontainers::count(const C& v,T val)
{
	typename C::const_iterator i=std::find(v.begin(),v.end(),val);
	int n=0;
	while(i!=v.end())
	{
		++n;
		++i; //skip the past element that we had just found
		i=std::find(i,v.end(),val);
	}
	return n;
}

int Ccontainers::copyFile(void)
{
	std::string from,to;
	std::cin>>from>>to;
	std::ifstream is(from.c_str()); //input stream
	std::istream_iterator<std::string> ii(is); //input iterator for stream
	std::istream_iterator<std::string> eos; //input sentinel

	std::vector<std::string> b(ii,eos); //b is a vector initialized from input
	std::sort(b.begin(),b.end()); //sort the buffer
	
	std::ofstream os(to.c_str()); //output stream
	std::ostream_iterator<std::string> oo(os,"\n"); //output iterator for output stream
	std::unique_copy(b.begin(),b.end(),oo); //copy buffer to output discarding replicated values
	return (!is.eof() && !os);	//return error state
}

