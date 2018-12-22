//#include <iterator>
#include <iostream>
#include <algorithm>

_STD_BEGIN
template <class _Tdata, class _Alloc = std::allocator<_Tdata> >
class gadiList : public _Container_base {
protected:
	//this is the class which hold the node links
	class _listNode
	{
	public:
		_listNode *_Next; //next node
		_listNode *_Prev; //previous node
		_Tdata	  _MyValue; //value
	private:
		_listNode &operator=(const _listNode &){}; //prevent the copying of the node
	};

public:
	//all those are neeed by the STL containter and comes from allocator 
	typedef _Alloc allocator_type;
    typedef typename _Alloc::value_type value_type; //type of the internal value
    typedef typename _Alloc::reference reference; //reference typedefef
	typedef typename _Alloc::pointer pointer; //pointer typedef
	typedef typename _Alloc::const_pointer const_pointer; //const pointer typedef
    typedef typename _Alloc::const_reference const_reference; //const reference typedef
    typedef typename _Alloc::difference_type difference_type; //diference type
    typedef typename _Alloc::size_type size_type; //size type
	//those are typical for list etc
	typedef _listNode* _NodePtr; //pointer to the node structure
	typedef _NodePtr& _Nodepref; //reference of the pointer to the node structure

	size_type _MySize; //nr of elements
	_NodePtr _Myhead; //head of the list
	/*
	Iterator will be bidirectional and inherit from _Interator012
	it will have the main container class const typedefs as template parameters
	*/
	template<class _MyList>
    class _iterator
		: public _Iterator012<bidirectional_iterator_tag,
			typename _MyList::value_type,
			typename _MyList::difference_type,
			typename _MyList::const_pointer,
			typename _MyList::const_reference,
			_Iterator_base0>
	{ 
    public:
		//common types inherited from the main container class
        typedef typename _MyList::difference_type difference_type; //diference type
        typedef typename _MyList::value_type value_type; //value type typedef
		typedef typename _MyList::size_type size_type; //size type typedef
		
		//those will be particular to const interator nor normal interator
        typedef typename _MyList::reference reference; //reference typedef
        typedef typename _MyList::pointer pointer; //pointer typedef
		
		//this will define the iterator category in case of the list it has to be bidirectional
        typedef bidirectional_iterator_tag iterator_category;
		
		//node pointer typedef
		typedef typename _MyList::_NodePtr _NodePtr;

		//default constructor (nothing to do)
        _iterator():_Ptr(0) {};

		//copy constructor
        _iterator(const _iterator<_MyList> &_Iter) : _Ptr(_Iter._Ptr) {};

		//normal constructor
		_iterator(const _NodePtr pNode) :_Ptr(pNode) {};

		//normal constructor which inherit a list
		_iterator(const _NodePtr pNode,const _MyList *_Plist) :_Ptr(pNode)
		{
			//this is necessary to adopt a list _Adopt is inherited from the base container
			this->_Adopt(_Plist);
		}
		
		//destructor (nothing to do)
        ~_iterator() {};

		//equality operator is mandatory in STL
        bool operator==(const _iterator& _Right) const
		{
			return(_Ptr==_Right._Ptr);
		};

		//inequality operator is mandatory in STL
        bool operator!=(const _iterator& _Right) const
		{
			return(!(_Ptr==_Right._Ptr));
		}

		//preincrement operator is mandatory in STL
        _iterator& operator++()
		{
			_Ptr=_MyList::_Nextnode(_Ptr);
			return(*this);
		};

		//predecrement operator is mandatory in STL
        _iterator& operator--()
		{
			_Ptr=_MyList::_Prevnode(_Ptr);
			return(*this);
		};

		//postincrement opreator is optional in STL
        _iterator operator++(int)
		{
			//we have to save the value first
			_iterator _tmp=*this;
			//next node from the list
			_Ptr=_MyList::_Nextnode(_Ptr);
			return(_tmp);
		}; //optional

		//postdecrement operator is optional in STL
        _iterator operator--(int)
		{
			//we have to save the value first
			_iterator _tmp=*this;
			//previous node from the list
			_Ptr=_MyList::_Prevnode(_Ptr);
			return(_tmp);
		}; //optional

		//derefrenciator operator is mandatory in STL
        reference operator*() const
		{
			return(_MyList::_Myval(_Ptr));
		};

		//class selection operator is mandatory in STL
        pointer operator->() const
		{
			//this is standard for STL
			return(_STD pointer_traits<pointer>::pointer_to(**this));
		}

		//get the node pointer
		_NodePtr _Mynode(void)
		{
			return(_Ptr);
		}
		
		//this store the pointer to the elment from the container by definition of the equivalence of the iterator
		_NodePtr _Ptr;
    };

	//constant iterator is the same as is for _interator except some particular settings: all pointer and reference becomes constant
	template<class _MyList>
    class _const_iterator
		: public _Iterator012<bidirectional_iterator_tag,
			typename _MyList::value_type,
			typename _MyList::difference_type,
			typename _MyList::const_pointer,
			typename _MyList::const_reference,
			_Iterator_base0>
	{
    public:
		//common types inherited from the main container class
        typedef typename _MyList::difference_type difference_type; //difference type typedef
        typedef typename _MyList::value_type value_type; //value type typedef
		
		//this define the const from the mutable iterator
        typedef typename _MyList::reference const_reference; //reference now becomes const_reference
        typedef typename _MyList::pointer const_pointer; //pointer now becomes const_pointer
		
		//for list the iterator category should be bidirectional
        typedef bidirectional_iterator_tag iterator_category;

		//pointer to the container element
		typedef typename _MyList::_NodePtr _NodePtr;

		//default iterator (nothing to do)
		_const_iterator () :_Ptr(0) {};
				
		//copy constructor
        _const_iterator (const _const_iterator<_MyList>& _Iter) : _Ptr(_Iter._Ptr) {};
		
		//conversion from nutuable iterator
        _const_iterator (const _iterator<_MyList>& _Iter) : _Ptr(_Iter._Ptr) {};

		//normal constructor which inherit a list
		_const_iterator(const _NodePtr pNode,const _MyList *_Plist) :_Ptr(pNode)
		{
			//this is necessary to adopt a list _Adopt is inherited from the base container
			this->_Adopt(_Plist);
		}

		//destructor (nothing to do)
        ~_const_iterator() {};

		//equality operator is mandatory in STL
		bool operator==(const _const_iterator<_MyList>& _Right) const
		{
			return(_Ptr==_Right._Ptr);
		};

		//inequality operator is mandatory in STL
        bool operator!=(const _const_iterator<_MyList>& _Right) const
		{
			return(!(_Ptr==_Right._Ptr));
		}

		//preincrement operator is mandatory in STL
        _const_iterator& operator++()
		{
			_Ptr=_MyList::_Nextnode(_Ptr);
			return((_const_iterator &)*this);
		};

		//post increment operator is optional in STL
        _const_iterator operator++(int)
		{
			_const_iterator _tmp=*this;
			_Ptr=_MyList::_Nextnode(_Ptr);
			return(_tmp);
		}; //optional

		//reference oprator is mandatory in STL
        const_reference operator*() const
		{
			return(const_reference(_Mylist::_Myval(_Ptr)));
		};

		//class selection is mandatory in STL
        const_pointer operator->() const
		{
			return(_STD pointer_traits<pointer>::pointer_to(**this));
		}

		//get the pointer to the element
		_NodePtr _Mynode(void)
		{
			return(_Ptr);
		}

		//conversion operator to mutable operator
		operator _iterator<_MyList>(){return(_iterator<_MyList>(_Ptr));}

		//storage of value
		_NodePtr _Ptr;
    };

	//typedefs of the real operator (those should be particular to each implementation
	//because they are templates they have to be particular to the classes
	typedef _iterator<gadiList> iterator; //mutable operator
	typedef _const_iterator<gadiList> const_iterator; //constant iterator
	
	//reverse iterators optionals in STL
    typedef std::reverse_iterator<iterator> reverse_iterator; //optional
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator; //optional
	
	//rebind node necessary for allocators
	typename _Alloc::template rebind<_listNode>::other _Alnod;	// allocator object for nodes

	//default constructor
    gadiList()
	{
		//construct the head which is the tag head
		this->_Myhead = new _listNode;
		//link the head to itself
		this->_Nextnode(this->_Myhead) = this->_Myhead;
		this->_Prevnode(this->_Myhead) = this->_Myhead;
		//it has no elements
		this->_MySize=0;
	};

	//copy constructor
    gadiList(const gadiList& _original)
	{
		//construct the head which is the tag head
		this->_Myhead = new _listNode;
		//link the head to itself
		this->_Nextnode(this->_Myhead) = this->_Myhead;
		this->_Prevnode(this->_Myhead) = this->_Myhead;
		//it has no elements
		this->_MySize=0;
		//now we should copy the elements
		for(gadiList::iterator i=_original.begin();i!=_original.end();++i)
		{
			this->push_back(*i);
		}
	};

	//destructor
    ~gadiList()
	{
		//clear the elements
		this->clear();
		//delete the head tag
		delete this->_Myhead;
	};

	//assign operator
    gadiList& operator=(const gadiList& _original)
	{
		this->clear();
		//now we should copy the elements
		for(gadiList::iterator i=_original.begin();i!=_original.end();++i)
		{
			this->push_back(*i);
		}		
		return(*this);
	};
	
	//equality operator
    bool operator==(const gadiList& _original) const
	{
		//toDO
		if(_original._MySize!=this->_MySize)
			return(false);
		for(iterator _iOrig=_original.begin(),_iThis=this->begin();_iOrig!=_original.end();++_iThis,++_iOrig)
			if(*_iOrig!=*_iThis)
				return(false);
		return(true);
	};

	//inequality operator
    bool operator!=(const gadiList& _original) const
	{
		return(!(*this==_original));
	};

	//return the mutable iterator to the begin of the container, this is mandatory in STL
    iterator begin()
	{
		//it has to be the next node from the head
		return(iterator(this->_Nextnode(this->_Myhead), this));
	};

	//return the const_iterator to the begin of the container, this is mandatory in STL
    const_iterator begin() const
	{
		//it has to be the next node from the head
		return(const_iterator(this->_Nextnode(this->_Myhead), this));
	};

	//return the mutable iterator to the end of the container, this is mandatory in STL
    iterator end()
	{
		//it has to be the head
		return(iterator(this->_Myhead,this));
	};

	//return the const_iterator to the end of the container, this is mandatory in STL
    const_iterator end() const
	{
		return(const_iterator(this->_Myhead,this));
	};

	//return the reference to the begin of the container, this is optional in STL, depend on the type of the container
    reference front() //optional
	{
		//just provide the refence from the begin operator
		return(*begin());
	};

	//return the reference to the end of the container, this is optional in STL, depend on the type of the container
	reference back() //optional
	{
		//it has to be the element in front of the end as described by the STL
		return(*(--end()));
	};

	//return the const_reference to the begin of the container, this is optional in STL, depend on the type of the container
    const_reference front() const //optional    
	{
		return(*begin());
	};

	//return the const_reference to the end of the container, this is optional in STL, depend on the type of the container
    const_reference back() const //optional
	{
		return(*(--end()));
	};

	// allocate a node and set links and value
	//here is done the allocation of the node of the list
	_NodePtr _Buynode(_NodePtr _Next, _NodePtr _Prev, const _Tdata& _Val)
	{
		//alocate a link node using allocator and not new
		_NodePtr _Pnode = this->_Alnod.allocate(1);
		//link the next node
		this->_Nextnode(_Pnode) = _Next;
		//link the previous node
		this->_Prevnode(_Pnode) = _Prev;
		//set the value
		_Pnode->_MyValue=_Val;
		return (_Pnode);
	};

	//insert a node at the position specified by the iterator
	void insert(iterator &_Where,const _Tdata& _Val)
	{
		//first get the node
		_NodePtr _Pnode = _Where._Mynode();
		//get the previous node
		_NodePtr _PrevNode=this->_Prevnode(_Pnode);
		//buy a node
		_NodePtr _Newnode = this->_Buynode(_Pnode,_PrevNode, _Val);
		//set the previous node
		this->_Prevnode(_Pnode) = _Newnode;
		//increase the size
		++(this->_MySize);
		//set the links to the previous-> next node
		this->_Nextnode(this->_Prevnode(_Newnode)) = _Newnode;
	};

	//push one element at the begining of the container, this is optional for all containers but mandatory for list
	void push_front(const _Tdata& _rValue) //optional
	{
		insert(begin(),_rValue);
	};
	
	//push one element at the end of the container, this is optional for all containers but mandatory for list
    void push_back(const _Tdata& _rValue) //optional
	{
		insert(end(),_rValue);
	};
	
	//erase the element at the iterator position, this is optional for STL, necesary for sequential containers
    iterator erase(const_iterator _Where) //optional
	{
		//obtain the node
		_NodePtr _Pnode = _Where._Mynode();
		//if is empty return head
		if(this->_Prevnode(_Pnode)==this->_Nextnode(_Pnode))
		{
			return(this->end());
		}
		//if is not empty
		if (_Pnode != this->_Myhead)
		{
			++_Where;
			//get the previous node
			_NodePtr _PrevNode=this->_Prevnode(_Pnode);
			//get the next node
			_NodePtr _NextNode=this->_Nextnode(_Pnode);
			//set the links
			this->_Nextnode(_PrevNode)=_NextNode;
			this->_Prevnode(_NextNode)=_PrevNode;
			//dealocate using allocator dealocate
			this->_Alnod.deallocate(_Pnode, 1);
			//decrease the size
			--this->_MySize;
		}
		return(iterator(_Where._Mynode(),this));
	};

	//erase all elements that are between two positions given by two iterators, this is optinal in STL
	iterator erase(const_iterator _First, const_iterator _Second) //optional
	{
		//erase the first element
		const_iterator _ret=erase(_First);
		//while is not finished erase the elements
		while(_ret!=_Second)
		{
			_ret=erase(_ret);
		}
		//finally erase the last element
		_ret=erase(_Second);
		return(_ret);
	};
	
	//clear the container, optional, this will remove all the elements from the container
	void clear() //optional
	{
		//erase all elements
		erase(this->begin(),this->end());
		//make the default settings for tag
		this->_Nextnode(this->_Myhead) = this->_Myhead;
		this->_Prevnode(this->_Myhead) = this->_Myhead;
		this->_MySize=0;
	};

	//pop one element from the begining of the container, this is optional for all containers but mandatory for list
	void pop_front() //optional
	{
		erase(begin());
	};

	//pop one element from the end of the container, this is optional for all containers but mandatory for list
    void pop_back() //optional
	{
		erase(--end());
	};

	//return the size of the container, mandatory in STL
	size_type size()
	{
		return(this->_MySize);
	};

	//return true is the container has no elements
	bool empty()
	{
		return (this->_MySize == 0);
	};

	//get the value at position _position
	reference at(size_type _position) //optional
	{
		iterator _listIt=this->begin();
		for(size_type i=0;i!=_position;++i)
			++_listIt;
		return(*_listIt);
	};
	
	//get the value at position _position
	const_reference at(size_type _position) const//optional
	{
		iterator _listIt=this->begin();
		for(size_type i=0;i!=_position;++i)
			++_listIt;
		return(*_listIt);
	};
	
	//swap two containers
	void swap(gadiList& _swapable) //optional
	{
		if(this==&_swapable) return;
		if(this->get_allocator()==_swapable.get_allocator())
		{
			//swap the base container
			this->_Swap_all(_swapable);
			//swap the head
			_NodePtr _pNode=_swapable._Myhead;
			_swapable._Myhead=this->_Myhead;
			this->_Myhead=_pNode;
			//swap the size
			size_type _tmp=_swapable._MySize;
			_swapable._MySize=this->_MySize;
			this->_MySize=_tmp;
		}
	};
	
	//return the allocator
	_Alloc get_allocator() //optional
	{
		return(_Alnod);
	};

	//return the max size of the container, this is given by the allocator
	size_type max_size()
	{
		return(this->get_allocator().max_size());
	}

/*
	const_iterator cbegin() const;
	const_iterator cend() const;
*/
protected:
	//next node
	static _Nodepref _Nextnode(_NodePtr _pNode)
	{
		return((_Nodepref)_pNode->_Next);
	};

	//previous node
	static _Nodepref _Prevnode(_NodePtr _pNode)
	{
		return((_Nodepref)_pNode->_Prev);
	};

	//get the value
	static reference _Myval(_NodePtr _pNode)
	{
		return((reference)_pNode->_MyValue);
	};
};

//template nonmbember swap function
template <class _Tdata, class _Alloc>
	void swap(gadiList<_Tdata,_Alloc>& _left, gadiList<_Tdata,_Alloc>& _right) //optional
{
	_left.swap(_right);
}
_STD_END