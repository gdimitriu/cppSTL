//#include <iterator>
#include <iostream>
#include <allocators>
#include <algorithm>

_STD_BEGIN
template <class _Tdata, class _Alloc = std::allocator<_Tdata> >
class gadiList : public _Container_base {
protected:
	//this is the class which hold the node links
	class _listNode
	{
	public:
		_listNode *_Next;
		_listNode *_Prev;
		_Tdata	  _MyValue;
	private:
		_listNode &operator=(const _listNode &){}; //prevent the copying of the node
	};

public:
	typedef _Alloc allocator_type;
    typedef typename _Alloc::value_type value_type; 
    typedef typename _Alloc::reference reference;
	typedef typename _Alloc::pointer pointer;
	typedef typename _Alloc::const_pointer const_pointer;
    typedef typename _Alloc::const_reference const_reference;
    typedef typename _Alloc::difference_type difference_type;
    typedef typename _Alloc::size_type size_type;
	typedef _listNode* _NodePtr;
	typedef _NodePtr& _Nodepref;	

	size_type _MySize; //nr of elements
	_NodePtr _Myhead; //head of the list

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
        typedef typename _MyList::difference_type difference_type;
        typedef typename _MyList::value_type value_type;
        typedef typename _MyList::reference reference;
        typedef typename _MyList::pointer pointer;
		typedef typename _MyList::size_type size_type;
        typedef bidirectional_iterator_tag iterator_category;
		typedef typename _MyList::_NodePtr _NodePtr;

        _iterator():_Ptr(0)
		{
			//toDO
		};
        _iterator(const _iterator<_MyList> &_Iter) : _Ptr(_Iter._Ptr)
		{
		};
		_iterator(const _NodePtr pNode) :_Ptr(pNode)
		{
			//toDo
		};
		_iterator(const _NodePtr pNode,const _MyList *_Plist) :_Ptr(pNode)
		{
			this->_Adopt(_Plist);
		}
        ~_iterator()
		{
			//toDO
		};

        bool operator==(const _iterator& _Right) const
		{
			return(_Ptr==_Right._Ptr);
		};
        bool operator!=(const _iterator& _Right) const
		{
			return(!(_Ptr==_Right._Ptr));
		}

        _iterator& operator++()
		{
			_Ptr=_MyList::_Nextnode(_Ptr);
			return(*this);
		};
        _iterator& operator--()
		{
			_Ptr=_MyList::_Prevnode(_Ptr);
			return(*this);
		};
        _iterator operator++(int)
		{
			_iterator _tmp=*this;
			_Ptr=_MyList::_Nextnode(_Ptr);
			return(_tmp);
		}; //optional
        _iterator operator--(int)
		{
			_iterator _tmp=*this;
			_Ptr=_MyList::_Prevnode(_Ptr);
			return(_tmp);
		}; //optional


        reference operator*() const
		{
			return(_MyList::_Myval(_Ptr));
		};
        pointer operator->() const
		{
			return(_STD pointer_traits<pointer>::pointer_to(**this));
		}
		_NodePtr _Mynode(void)
		{
			return(_Ptr);
		}
		_NodePtr _Ptr;
    };

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
        typedef typename _MyList::difference_type difference_type;
        typedef typename _MyList::value_type value_type;
        typedef typename _MyList::reference const_reference;
        typedef typename _MyList::pointer const_pointer;
        typedef bidirectional_iterator_tag iterator_category;
		typedef typename _MyList::_NodePtr _NodePtr;

        _const_iterator ()
		{
			//toDO
		};
		_const_iterator (const _const_iterator& _Iter): _Ptr(_Iter._Ptr)
		{
		};
        _const_iterator (const _iterator<_MyList>& _Iter) : _Ptr(_Iter._Ptr)
		{
		};
        ~_const_iterator()
		{
			//toDO
		};

		bool operator==(const _iterator<_MyList>& _Right) const
		{
			return(_Ptr==_Right._Ptr);
		};
        bool operator!=(const _iterator<_MyList>& _Right) const
		{
			return(!(_Ptr==_Right._Ptr));
		}

        _const_iterator& operator++()
		{
			_Ptr=_MyList::_Nextnode(_Ptr);
			return((_const_iterator &)*this);
		};
        _const_iterator operator++(int)
		{
			_const_iterator _tmp=*this;
			_Ptr=_MyList::_Nextnode(_Ptr);
			return(_tmp);
		}; //optional

        const_reference operator*() const
		{
			return(const_reference(_Mylist::_Myval(_Ptr)));
		};

        const_pointer operator->() const
		{
			return(_STD pointer_traits<pointer>::pointer_to(**this));
		}

		_NodePtr _Mynode(void)
		{
			return(_Ptr);
		}

		_NodePtr _Ptr;
    };

	typedef _iterator<gadiList> iterator;
	typedef _const_iterator<gadiList> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator; //optional
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator; //optional
	typename _Alloc::template rebind<_listNode>::other _Alnod;	// allocator object for nodes

    gadiList()
	{
		this->_Myhead = new _listNode;
		this->_Nextnode(this->_Myhead) = this->_Myhead;
		this->_Prevnode(this->_Myhead) = this->_Myhead;
		this->_MySize=0;
	};
    gadiList(const gadiList&)
	{
		//toDO
	};
    ~gadiList()
	{
		//toDO
	};

    gadiList& operator=(const gadiList&);
    bool operator==(const gadiList&) const;
    bool operator!=(const gadiList&) const;

    iterator begin()
	{
		return(iterator(this->_Nextnode(this->_Myhead), this));
	};
    const_iterator begin() const
	{
		return(const_iterator(this->_Nextnode(this->_Myhead), this));
	}
    iterator end()
	{
		return(iterator(this->_Myhead,this));
	};
    const_iterator end() const
	{
		return(const_iterator(this->_Myhead,this));
	};
/*
	const_iterator cbegin() const;
	const_iterator cend() const;
*/
    reference front() //optional
	{
		return(*begin());
	}
	reference back() //optional
	{
		return(*(--end()));
	}
    const_reference front() const //optional    
	{
		return(*begin());
	}
    const_reference back() const //optional
	{
		return(*(--end()));
	}

	_NodePtr _Buynode(_NodePtr _Next, _NodePtr _Prev, const _Tdata& _Val)
	{	// allocate a node and set links and value

		_NodePtr _Pnode = new _listNode;

		this->_Nextnode(_Pnode) = _Next;
		this->_Prevnode(_Pnode) = _Prev;
		_Pnode->_MyValue=_Val;
		return (_Pnode);
	}
	void insert(iterator &_Where,const _Tdata& _Val)
	{
		_NodePtr _Pnode = _Where._Mynode();
		_NodePtr _PrevNode=this->_Prevnode(_Pnode);

		_NodePtr _Newnode = this->_Buynode(_Pnode,_PrevNode, _Val);
		this->_Prevnode(_Pnode) = _Newnode;
		++(this->_MySize);
		this->_Nextnode(this->_Prevnode(_Newnode)) = _Newnode;
	}

	void push_front(const _Tdata& _rValue) //optional
	{
		insert(begin(),_rValue);
	}

    void push_back(const _Tdata& _rValue) //optional
	{
		insert(end(),_rValue);
	};
	
    iterator erase(const_iterator _Where) //optional
	{
		_NodePtr _Pnode = (_Where++)._Mynode();
		if (_Pnode != this->_Myhead)
		{
			_NodePtr _PrevNode=this->_Prevnode(_Pnode);
			_NodePtr _NextNode=this->_Nextnode(_Pnode);
			this->_Nextnode(_PrevNode)=_NextNode;
			this->_Prevnode(_NextNode)=_PrevNode;
			this->_Alnod.deallocate(_Pnode, 1);
			--this->_MySize;
		}
		return(iterator(_Where._Mynode(),this));
	}

	void pop_front() //optional
	{
		erase(begin());
	}

    void pop_back() //optional
	{
		erase(--end());
	}
/*
	reference at(size_type); //optional
    const_reference at(size_type) const; //optional
    iterator erase(const_iterator, const_iterator); //optional
    void clear(); //optional
*/
	void swap(const gadiList&);

	size_type size()
	{
		return(this->_MySize);
	};
//    size_type max_size();

	bool empty()
	{
		return (this->_MySize == 0);
	};
    
	_Alloc get_allocator(); //optional

protected:
	//next node
	static _Nodepref _Nextnode(_NodePtr _pNode)
	{
		return((_Nodepref)_pNode->_Next);
	}
	//previous node
	static _Nodepref _Prevnode(_NodePtr _pNode)
	{
		return((_Nodepref)_pNode->_Prev);
	}
	//get the value
	static reference _Myval(_NodePtr _pNode)
	{
		return((reference)_pNode->_MyValue);
	}	
};
_STD_END
/*
template <class _Tdata, class _Alloc = std::allocator<_Tdata> >
	void std::swap(gadiList<_Tdata,_Alloc>&, gadiList<_Tdata,_Alloc>&); //optional
*/