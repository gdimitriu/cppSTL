#include "StdAfx.h"
#include "ArrayClass.h"
#include <iostream>

using namespace std;


CArrayClass::CArrayClass(void)
{
	m_first_entry=NULL;
	m_actualsize=0;
}


CArrayClass::~CArrayClass(void)
{
	CArray_element *current_location;
	while(1)
	{
		if(NULL!=m_first_entry)
		{
			current_location=m_first_entry;
			m_first_entry=m_first_entry->m_pnext;
			delete current_location;
		}
		else
		{
			break;
		}
	}
}

int CArrayClass::set(int item, int index)
{
	if(0==m_read_only)
	{
		return -2;
	}
	if(m_actualsize<index)
	{
		return -1;
	}
	else
	{
		CArray_element *iterator;
		int iterator_pos=0;
		iterator=m_first_entry;
		while(1)
		{
			if(iterator==NULL)
			{
				break;
			}
			if(iterator_pos==index)
			{
				iterator->m_data=item;
				return 0;
			}
			iterator=iterator->m_pnext;
			++iterator_pos;
		}
		return -1;
	}
}

	int CArrayClass::add(int item)
	{
		if(0==m_read_only)
		{
			return -2;
		}
		CArray_element *new_elem;
		new_elem=new CArray_element(item);
		if(NULL==m_first_entry)
		{
			m_first_entry=new_elem;
			m_last_entry=new_elem;
			++m_actualsize;
		}
		else
		{
			m_last_entry->m_pnext=new_elem;
			m_last_entry=new_elem;
			++m_actualsize;
		}
		return 0;
	}


	int CArrayClass::set_ro(void)
	{
		m_read_only=0;
		return 0;
	}


	int CArrayClass::get(int index,int &item)
	{
		if(index>m_actualsize)
		{
			return -1;
		}
		else
		{
			CArray_element *iterator;
			int iterator_pos=0;
			iterator=m_first_entry;
			while(1)
			{
				if(iterator==NULL)
				{
					break;
				}
				if(iterator_pos==index)
				{
					item=iterator->m_data;
					return 0;
				}
				iterator=iterator->m_pnext;
				++iterator_pos;
			}
			return -1;
		}
		return -1;
	}

	void CArrayClass::print(void)
	{
		int item,i;
		for(i=0;i<m_actualsize;++i)
		{
			if(0==get(i,item))
			{
				cout<<item<<"\n";
			}
		}
	}

	void CArrayClass::test(void)
	{
		add(5);
		add(6);
		add(7);
		print();
		set_ro();
		test_readonly();
		set_rw();
		set(8,2);		
		print();
	}

	void CArrayClass::set_rw(void)
	{
		m_read_only=1;
	}

	int CArrayClass::test_readonly(void)
	{
		int item;
		int test_pos;
		if(add(10)==-2)
		{
			cout<<"read only write request\n";
			test_pos=m_actualsize-1;
			if(test_pos>0)
			{
				if(0==get(test_pos,item))
				{
					cout<<"read only get request correct"<<"\n";
				}
				else
				{
					return(-1);
				}
			}
			return 0;
		}
	}