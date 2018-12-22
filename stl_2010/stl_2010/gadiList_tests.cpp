#include "gadiList.h"
#include "gadiList_tests.h"
#include <cassert>
#include <list>
#include <iterator>
#include <iostream>
namespace _gadiList_unitests
{
	using namespace std;
	/*template for test class */
	template<typename _TData>
	class holdData
	{
	private:
		_TData _value;
	public:
		holdData(){_value=0;};
		holdData(_TData _val) : _value(_val) {};
		holdData(const holdData &_old) : _value(_old._value) {};
		//assign operator
		holdData &operator=(const holdData &_old)
		{
			_value=_old._value;
			return(*this);
		}
		virtual ~holdData(){};
		//return the hold value
		inline _TData GetValue(){return(_value);};
		//conversion operator so no need for operator << or some other operator
		//this is neeed by copy template also
		operator _TData() { return(_value);};
	};

	void front_tests(void)
	{
		//create the test vector
		list<int> _list;
		for(int i=0;i<10;++i)
			_list.push_back(i);
		//now create the list
		gadiList<holdData<int>> _testList;
		for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
		{
			_testList.push_front(holdData<int>(*i));
		}
		int j=9;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			--j;
		}
		assert(-1==j);
		//test the front
		assert(9==_testList.front());
		//output to the stdout
		cout<<endl;
		ostream_iterator<int> output_it(cout," ");
		copy(_testList.begin(),_testList.end(),output_it);
		cout<<endl;
		//pop the front
		_testList.pop_front();
		//test the rest of the elements
		j=8;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			--j;
		}
		assert(-1==j);
		cout<<"Front tests passed"<<endl;
	}

	void back_tests(void)
	{
		//create the test vector
		list<int> _list;
		for(int i=0;i<10;++i)
			_list.push_back(i);
		//now create the list
		gadiList<holdData<int>> _testList;
		for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
		{
			_testList.push_back(holdData<int>(*i));
		}
		int j=0;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(10==j);
		//test the front
		assert(9==_testList.back());
		//output to the stdout
		cout<<endl;
		ostream_iterator<int> output_it(cout," ");
		copy(_testList.begin(),_testList.end(),output_it);
		cout<<endl;
		//pop the front
		_testList.pop_back();
		//test the rest of the elements
		j=0;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(j==9);
		cout<<"Back tests passed"<<endl;
	}

	void erase_tests(void)
	{
		//create the test vector
		list<int> _list;
		for(int i=0;i<10;++i)
			_list.push_back(i);
		//now create the list
		gadiList<holdData<int>> _testList;
		for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
		{
			_testList.push_back(holdData<int>(*i));
		}
		int j=0;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(10==j);
		//erase the last element
		assert(9==_testList.back());
		_testList.erase(--_testList.end());
		assert(8==_testList.back());
		//now test the multiple erase
		gadiList<holdData<int>>::iterator _first;
		gadiList<holdData<int>>::iterator _second;
		for(_first=_testList.begin(),j=0;j<2 && _first!=_testList.end();++j,++_first); //left empty
		for(_second=_first,j=0;j<3 && _second!=_testList.end();++j,++_second); //left empty
		_testList.erase(_first,_second);
		gadiList<holdData<int>>::iterator i;
		for(i=_testList.begin(),j=0;j<2;++j,++i)
			assert(j==*i);
		for(j=6;j<9;++j,++i)
			assert(j==*i);
		//test the clear list
		_testList.clear();
		assert(0==_testList.size());
		for(j=0,i=_testList.begin();i!=_testList.end();++i,++j);
		assert(0==j);
		cout<<"Erase testes passed"<<endl;
	}

	void constructor_tests(void)
	{
		//create the test vector
		list<int> _list;
		for(int i=0;i<10;++i)
			_list.push_back(i);
		//now create the list
		gadiList<holdData<int>> _testList;
		for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
		{
			_testList.push_back(holdData<int>(*i));
		}
		int j=0;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(10==j);
		gadiList<holdData<int>> _testListnew(_testList);
		j=0;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(10==j);
		gadiList<holdData<int>> _testList_assign;
		for(j=0;j<10;++j)
			_testList_assign.push_back(holdData<int>(j*100));
		_testList_assign=_testList;
		j=0;
		for(gadiList<holdData<int>>::iterator i=_testList_assign.begin();i!=_testList_assign.end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(10==j);
		cout<<"constructor tests passed"<<endl;
	}

	void equality_tests(void)
	{
		list<int> _list;
		for(int i=0;i<10;++i)
			_list.push_back(i);
		//now create the list
		gadiList<holdData<int>> _testList;
		for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
		{
			_testList.push_back(holdData<int>(*i));
		}
		int j=0;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(10==j);
		gadiList<holdData<int>> _testListnew(_testList);
		j=0;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(10==j);
		assert(_testList==_testListnew);
		//delete an element
		_testListnew.erase(--_testListnew.end());
		assert(_testList!=_testListnew);
		//now add an element
		_testListnew.push_back(holdData<int>(100));
		assert(_testList!=_testListnew);
		//now delete the element
		_testListnew.erase(--_testListnew.end());
		//now add the original element and both containers should be equivalent
		_testListnew.push_back(holdData<int>(9));
		assert(_testList==_testListnew);
		assert(3==_testList.at(3));
		cout<<"equality test passed"<<endl;
	}

	void dynamical_tests(void)
	{
		list<int> _list;
		for(int i=0;i<10;++i)
			_list.push_back(i);
		//now create the list
		gadiList<holdData<int>> *_testList=new gadiList<holdData<int>>;
		for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
		{
			_testList->push_back(holdData<int>(*i));
		}
		int j=0;
		for(gadiList<holdData<int>>::iterator i=_testList->begin();i!=_testList->end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(10==j);
		//delete an element
		_testList->erase(--_testList->end());
		j=0;
		for(gadiList<holdData<int>>::iterator i=_testList->begin();i!=_testList->end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(9==j);
		delete _testList;
		cout<<"dynamical tests passed"<<endl;
	}
	
	void swap_tests(void)
	{
		list<int> _list;
		for(int i=0;i<10;++i)
			_list.push_back(i);
		//now create the list
		gadiList<holdData<int>> _testList;
		for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
		{
			_testList.push_back(holdData<int>(*i));
		}
		int j=0;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j==*i);
			++j;
		}
		assert(10==j);
		gadiList<holdData<int>> _testListnew;
		for(list<int>::iterator i=_list.begin();i!=_list.end();++i)
		{
			_testListnew.push_back(holdData<int>((*i)*100));
		}
		j=0;
		for(gadiList<holdData<int>>::iterator i=_testListnew.begin();i!=_testListnew.end();++i)
		{
			assert(j*100==*i);
			++j;
		}
		assert(10==j);
		_testList.swap(_testListnew);
		j=0;
		for(gadiList<holdData<int>>::iterator i=_testList.begin();i!=_testList.end();++i)
		{
			assert(j*100==*i);
			++j;
		}
		std::swap(_testList,_testListnew);
		j=0;
		for(gadiList<holdData<int>>::iterator i=_testListnew.begin();i!=_testListnew.end();++i)
		{
			assert(j*100==*i);
			++j;
		}
		cout<<"swap test paseed"<<endl;
	}
}
void run_tests(void)
{
	_gadiList_unitests::front_tests();
	_gadiList_unitests::back_tests();
	_gadiList_unitests::erase_tests();
	_gadiList_unitests::constructor_tests();
	_gadiList_unitests::equality_tests();
	_gadiList_unitests::dynamical_tests();
	_gadiList_unitests::swap_tests();
}