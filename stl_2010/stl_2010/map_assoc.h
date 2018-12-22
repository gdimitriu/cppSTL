/* map as STL container implemented with vector */
#pragma once
#include <vector>
#include <algorithm>
#include <functional>
void map_ssoc_run_all_unitests(void);

_STD_BEGIN
template<typename _TdataKey,typename _TdataValue,typename _Tdataequalfunc,typename _Tdatalessfunc,
	class _AllocValue = std::allocator<_TdataValue>,class _AllocKey = std::allocator<_TdataKey>>
class map_assoc : public _Container_base
{
protected:
	//this is the pair
	typedef typename std::pair<_TdataKey,_TdataValue> _mapPair;

	//function to provide less compareson only for the key
	bool _lessPair(_mapPair left,_mapPair right)
	{
		return _less_fn(left.first,right.first);
	}

	//function to provide equal compareson only for the key
	bool _equalPair(_mapPair& left,_mapPair& right)
	{
		return _equal_fn(left.first,right.first);
	}

	//storage vector
	std::vector<_mapPair> _storage;

	//compareson functions
	typename _Tdataequalfunc _equal_fn;
	typename _Tdatalessfunc _less_fn;
	typedef typename std::vector<_mapPair>::iterator _intIterator;
public:
	//all those are neeed by the STL containter and comes from allocator 
	typedef _AllocValue allocator_type;
    typedef typename _AllocValue::value_type value_type; //type of the internal value
    typedef typename _AllocValue::reference reference; //reference typedefef
	typedef typename _AllocValue::pointer pointer; //pointer typedef
	typedef typename _AllocValue::const_pointer const_pointer; //const pointer typedef
    typedef typename _AllocValue::const_reference const_reference; //const reference typedef
    typedef typename _AllocValue::difference_type difference_type; //diference type
    typedef typename _AllocValue::size_type size_type; //size type
	//default constructor
	map_assoc(){};
/*
	Iterator will be bidirectional and inherit from _Interator012
	it will have the main container class const typedefs as template parameters
	*/
	template<class _map>
    class _iterator
		: public _Iterator012<bidirectional_iterator_tag,
			typename _map::value_type,
			typename _map::difference_type,
			typename _map::const_pointer,
			typename _map::const_reference,
			_Iterator_base0>
	{
	public:
		//common types inherited from container
		typedef typename _map::value_type value_type;
		typedef typename _map::size_type size_type;
		typedef typename _map::difference_type difference_type;
		//those will be particular to each iterator
		typedef typename _map::reference reference;
		typedef typename _map::pointer pointer;
		typedef bidirectional_iterator_tag iterator_tag;
		typedef typename _map::pair_type _pair;
		typedef typename _map::_intIterator _intIterator;

		//constructor
		_iterator(){};
		_iterator(_intIterator it):_int_iterator(it){};
		_iterator(_iterator &it)
		{
			_int_iterator=it._int_iterator;
		}
		//== operator
		bool operator==(_iterator right)
		{
			return(_int_iterator==right._int_iterator);
		}
		bool operator!=(_iterator right)
		{
			return(!(*this==right));
		}
		//++operator
		_iterator& operator++()
		{
			++_int_iterator;
			return(*this);
		}
		//--operator
		_iterator& operator--()
		{
			--_int_iterator;
			return(*this);
		}
		//class selection operator is mandatory in STL
        pointer operator->() const
		{
			//this is standard for STL
			return(_STD pointer_traits<pointer>::pointer_to(**this));
		}
		//operator *
		reference operator*()
		{
			return((*_int_iterator).second);
		}
		//get the pair
		_mapPair getPair()
		{
			return(*_int_iterator);
		}
	protected:
		//internal iterator
		_intIterator _int_iterator;
	};
public:
	//typedefs of the real operator (those should be particular to each implementation
	//because they are templates they have to be particular to the classes
	typedef _iterator<map_assoc> iterator; //mutable operator
	//external definition for the pair
	typedef typename _mapPair pair_type;
	
	//begin iterator position
	iterator begin()
	{
		return(iterator(_storage.begin()));
	}
	//end iterator position
	iterator end()
	{
		return(iterator(_storage.end()));
	}
	//insert operation
	iterator insert(_TdataKey key,_TdataValue val)
	{
		_intIterator pos;
		pair_type toInsert(key,val);
		if(_storage.empty())
		{
			_storage.push_back(toInsert);
			pos=_storage.end();
			return(iterator(--pos));
		}
		if(_less_fn(key,(*_storage.begin()).first))
		{
			_storage.insert(_storage.begin(),toInsert);
			return(iterator(_storage.begin()));
		}
		pos=std::lower_bound(_storage.begin(),_storage.end(),toInsert,
			std::bind(&map_assoc::_lessPair,this,std::placeholders::_1,std::placeholders::_2)
						);
		if(pos==_storage.end())
		{
			_storage.push_back(toInsert);
			pos=_storage.end();
			return(iterator(--pos));
		}
		if(_equal_fn((*pos).first,key))
		{
			(*pos).second=val;
			return(iterator(pos));
		}
		if(_less_fn(key,(*pos).first))
		{
			_storage.insert(pos,toInsert);
			return(iterator(pos));
		}
		return(iterator(_storage.end()));
	}
	//find operation
	_TdataValue find(_TdataKey key)
	{
		_intIterator pos;
		_TdataValue val;
		pair_type toFind(key,val);
		pos=std::find_if(_storage.begin(),_storage.end(),std::bind(&map_assoc::_equalPair,this,std::placeholders::_1,toFind));
		if(pos==_storage.end())
			return(val);
		return ((*pos).second);
	}

	//clear operation
	void clear(void)
	{
		_storage.clear();
	}

	//empty
	bool empty(void)
	{
		return(_storage.empty());
	}
	
	//size
	size_type size(void)
	{
		return(_storage.size());
	}
	
	//max size
	size_type max_size(void)
	{
		return(_storage.max_size());
	}

	void erase(_TdataKey key)
	{
		_TdataValue val;
		pair_type toDelete(key,val);
		_intIterator pos;
		pos=std::find_if(_storage.begin(),_storage.end(),std::bind(&map_assoc::_equalPair,this,std::placeholders::_1,toDelete));
		if(pos==_storage.end())
			return;
		_storage.erase(pos);
	}

	reference operator[](const _TdataKey key)
	{
		_TdataValue val(0);
		pair_type toFind(key,val);
		_intIterator pos;
		if(_storage.empty() || _lessPair(_storage.back(),toFind))
		{
			_storage.push_back(toFind);
			return(_storage.back().second);
		}
		if(_lessPair(toFind,*_storage.begin()))
		{
			pos=_storage.insert(_storage.begin(),toFind);
			return((*pos).second);
		}
		pos=std::lower_bound(_storage.begin(),_storage.end(),toFind,std::bind(&map_assoc::_lessPair,this,std::placeholders::_1,std::placeholders::_2));
		if(!_equalPair(*pos,toFind))
			pos=_storage.insert(pos,toFind);
		return((*pos).second);
	}
};
_STD_END