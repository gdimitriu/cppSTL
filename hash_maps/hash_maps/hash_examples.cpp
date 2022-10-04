#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <hash_map>
#include <map>
#include <cassert>
#include "DataCompare.h"
#include "efficient_operations.h"

void hash_map_tests(void)
{
	std::cout<<"start hash_map::run_tests"<<std::endl;
	std::vector<int> _tst;
	_tst.push_back(7);
	_tst.push_back(9);
	_tst.push_back(12);
	_tst.push_back(14);
	_tst.push_back(17);
	_tst.push_back(19);
	_tst.push_back(23);
	_tst.push_back(50);
	_tst.push_back(54);
	_tst.push_back(67);
	_tst.push_back(72);
	_tst.push_back(76);
	std::hash_map<int,int> _AVL;

	for(std::vector<int>::iterator it=_tst.begin();it!=_tst.end();++it)
	{
		_AVL.insert(std::pair<int,int>(*it,*it));
	}
	std::cout<<"end hash_map::run_tests containers"<<std::endl;
	std::sort(_tst.begin(),_tst.end());
	std::hash_map<int,int>::iterator hashIt=_AVL.begin();
	std::vector<int>::iterator it=_tst.begin();
	for(;hashIt!=_AVL.end();++it,++hashIt)
	{
		std::cout<<*it<<" vs " <<hashIt->second<<std::endl;
	}
	std::cout<<std::endl;
	std::cout<<"now in reverse order\n";
	std::hash_map<int,int>::reverse_iterator rhashIt=_AVL.rbegin();
	std::vector<int>::reverse_iterator rIt=_tst.rbegin();
	for(;rhashIt!=_AVL.rend();++rIt,++rhashIt)
	{
		std::cout<<*rIt<<" vs " <<rhashIt->second<<std::endl;
	}
	std::cout<<std::endl;
	hashIt=_AVL.find(50);
	if(hashIt!=_AVL.end())
	{
		std::cout<<"here is it\n";
	}
	_AVL.clear();
}

void map_vector_tests(void)
{
	std::cout<<"start vectorReplace::run_tests"<<std::endl;
	std::vector<int> _tst;
	_tst.push_back(7);
	_tst.push_back(9);
	_tst.push_back(12);
	_tst.push_back(14);
	_tst.push_back(17);
	_tst.push_back(19);
	_tst.push_back(23);
	_tst.push_back(50);
	_tst.push_back(54);
	_tst.push_back(67);
	_tst.push_back(72);
	_tst.push_back(76);
	std::vector<Data> _AVL;

	for(std::vector<int>::iterator it=_tst.begin();it!=_tst.end();++it)
	{
		_AVL.push_back(std::pair<int,int>(*it,*it));
	}
	std::sort(_tst.begin(),_tst.end());
	std::sort(_AVL.begin(),_AVL.end(),DataCompare());
	std::vector<Data>::iterator hashIt=_AVL.begin();
	std::vector<int>::iterator it=_tst.begin();
	for(;hashIt!=_AVL.end();++it,++hashIt)
	{
		std::cout<<*it<<" vs " <<hashIt->second<<std::endl;
	}
	std::cout<<std::endl;
	std::cout<<"now in reverse order\n";
	std::vector<Data>::reverse_iterator rhashIt=_AVL.rbegin();
	std::vector<int>::reverse_iterator rIt=_tst.rbegin();
	for(;rhashIt!=_AVL.rend();++rIt,++rhashIt)
	{
		std::cout<<*rIt<<" vs " <<rhashIt->second<<std::endl;
	}
	if(std::binary_search(_AVL.begin(),_AVL.end(),50,DataCompare()))
	{
		std::cout<<"here is found\n";
	}
	std::cout<<std::endl;
	std::map<int,int> _Map;
	for(std::vector<int>::iterator it=_tst.begin();it!=_tst.end();++it)
		efficientAndOrUpdate(_Map,*it,*it);
	_Map[50]=51;
	efficientAndOrUpdate(_Map,76,78);
	for(std::map<int,int>::iterator MapIt=_Map.begin();MapIt!=_Map.end();++MapIt)
	{
		std::cout<<MapIt->first<<" vs "<<MapIt->second<<std::endl;
	}
	_AVL.clear();
}