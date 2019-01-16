#include"map_assoc.h"
#include <string>
#include <iostream>
#include <cassert>
#include <functional>
#include <vector>
using std::map_assoc;
using std::string;
using std::vector;

void map_ssoc_run_all_unitests(void)
{
	vector<string> _temp;
	_temp.push_back("aaa");
	_temp.push_back("a32");
	_temp.push_back("a1");
	_temp.push_back("a23");
	_temp.push_back("a23");
	_temp.push_back("a1");
	typedef map_assoc<string,int,std::equal_to<string>,std::less<string>> map_string_int;
	map_string_int _mapTest;
	map_string_int::iterator _iterator;
	std::pair<string,int> _pair;
	_mapTest.insert(string("aaa"),1);
	_mapTest.insert(string("a32"),1);
	_mapTest.insert(string("a1"),2);
	_mapTest.insert(string("a23"),2);
	for(_iterator=_mapTest.begin();_iterator!=_mapTest.end();++_iterator)
	{
		_pair=_iterator.getPair();
		std::cout<<*_iterator<<std::endl;
	}
	std::cout<<"now find the value a23=";
	std::cout<<_mapTest.find(string("a23"))<<std::endl;
	std::cout<<"now delete the aaa"<<std::endl;
	_mapTest.erase(string("aaa"));
	for(_iterator=_mapTest.begin();_iterator!=_mapTest.end();++_iterator)
	{
		std::cout<<*_iterator<<std::endl;
	}
	std::cout<<"end normal tests"<<std::endl;
	_mapTest.clear();
	std::cout<<"begin reference tests"<<std::endl;
	for(vector<string>::iterator it=_temp.begin();it!=_temp.end();++it)
	{
		_mapTest[*it]++;
	}
	for(_iterator=_mapTest.begin();_iterator!=_mapTest.end();++_iterator)
	{
		std::cout<<*_iterator<<std::endl;
	}
	std::cout<<"end all tests";
}