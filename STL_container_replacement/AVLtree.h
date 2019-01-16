#pragma once
#include <iostream>
#include <allocators>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
using std::vector;
using std::stack;
//#define DEBUG 1
//for unitests
void AVLtree_run_all_tests(void);

_STD_BEGIN
template <class _Tdata, class _Alloc = std::allocator<_Tdata> >
class AVLtree: public _Container_base
{
private:
	class _node
	{
	private:
		int _height;
		int _balance;
		int _count;
		_node *_left;
		_node *_right;
		_node *_parent;
	public:
		_Tdata _value;
		_node(_Tdata val):_value(val)
		{
			_left=nullptr;
			_right=nullptr;
			_parent=nullptr;
			_count=1;
			_height=0;
			_balance=0;
		}
		int updateHeight()
		{
			int lh=0;
			if(_left!=nullptr) lh=_left->updateHeight();
			int rh=0;
			if(_right!=nullptr) rh=_right->updateHeight();
			if(lh<rh) _height=rh;
			else _height=lh;
			_balance=rh-lh;
			return _height+1;
		}
		//gethere
		_Tdata getValue(){ return _value;}
		int getHeight(){return _height;}
		int getBalance() {return _balance;}
		int getCount() {return _count;}
		_node*& getLeft(){return _left;}
		_node*& getRight(){return _right;}
		_node*& getParent(){return _parent;}
		//setere
		void setHeight(int val){_height=val;}
		void setBalance(int val) {_balance=val;}
		void setCount(int val){_count=val;}
		void setValue(_Tdata val) {_value=val;}
		void setLeft(_node *val){_left=val;}
		void setRight(_node *val){_right=val;}
		void setParent(_node *val){_parent=val;}
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
	//those are for the tree definition
	typedef typename _node* _NodePtr;//pointer to the node structure
	typedef typename _NodePtr& _Nodepref; //reference of the pointer to the node structure
private:
	_NodePtr _headPtr;
	int _size;
	_NodePtr _currentPosPtr;
public:
	/*
	Iterator will be bidirectional and inherit from _Interator012
	it will have the main container class const typedefs as template parameters
	*/
	template<class _AVLtree>
    class _iterator
		: public _Iterator012<bidirectional_iterator_tag,
			typename _AVLtree::value_type,
			typename _AVLtree::difference_type,
			typename _AVLtree::const_pointer,
			typename _AVLtree::const_reference,
			_Iterator_base0>
	{ 
    public:
		//common types inherited from the main container class
        typedef typename _AVLtree::difference_type difference_type; //diference type
        typedef typename _AVLtree::value_type value_type; //value type typedef
		typedef typename _AVLtree::size_type size_type; //size type typedef
		
		//those will be particular to const interator nor normal interator
        typedef typename _AVLtree::reference reference; //reference typedef
        typedef typename _AVLtree::pointer pointer; //pointer typedef
		
		//this will define the iterator category in case of the list it has to be bidirectional
        typedef bidirectional_iterator_tag iterator_category;
		
		//node pointer typedef
		typedef typename _AVLtree::_NodePtr _NodePtr;

		//default constructor (nothing to do)
        _iterator():_Ptr(0) {};

		//copy constructor
		_iterator(const _iterator<_AVLtree> &_Iter) : _Ptr(_Iter._Ptr){};
			
		//normal constructor
		_iterator(const _NodePtr head)
		{
			_Ptr=_AVLtree::_NextNodeOrderInit(head,_CurrentPtrLRR,nullptr,_stackLRR);
		};
		//find constructor
		_iterator(_NodePtr head,_Tdata val)
		{
			_Ptr=_AVLtree::_NextNodeOrderInit(head,_CurrentPtrLRR,val,_stackLRR);
		}
		_iterator(const _NodePtr pNode,_NodePtr head)
		{
			if(pNode==nullptr)
			{
				_Ptr=nullptr;
				_CurrentPtrLRR=nullptr;
				return;
			}
			_Ptr=_AVLtree::_NextNodeOrderInit(head,_CurrentPtrLRR,pNode,_stackLRR);
		};

		//normal constructor which inherit a list
		_iterator(const _NodePtr pNode,const _AVLtree *_Plist) :_Ptr(pNode)
		{
			//this is necessary to adopt a list _Adopt is inherited from the base container
			this->_Adopt(_Plist);
		}
		
		//destructor (nothing to do)
        ~_iterator() {};

		//equality operator is mandatory in STL
        bool operator==(const _iterator& _Right) const
		{
			return(_Ptr==_Right._Ptr && _CurrentPtr==_Right._CurrentPtr);
		};

		//inequality operator is mandatory in STL
        bool operator!=(const _iterator& _Right) const
		{
			return(!(_Ptr==_Right._Ptr));
		}

		//preincrement operator is mandatory in STL
        _iterator& operator++()
		{
			_Ptr=_AVLtree::_NextNodeOrder(_stackLRR,_CurrentPtrLRR);
			return(*this);
		};

		//predecrement operator is mandatory in STL
        _iterator& operator--()
		{
			_Ptr=_AVLtree::_PrevNode(_Ptr);
			return(*this);
		};

		//postincrement opreator is optional in STL
        _iterator operator++(int)
		{
			//we have to save the value first
			_iterator _tmp=*this;
			//next node from the list
			_Ptr=_AVLtree::_NextNode(_Ptr);
			return(_tmp);
		}; //optional

		//postdecrement operator is optional in STL
        _iterator operator--(int)
		{
			//we have to save the value first
			_iterator _tmp=*this;
			//previous node from the list
			_Ptr=_AVLtree::_PrevNode(_Ptr);
			return(_tmp);
		}; //optional

		//derefrenciator operator is mandatory in STL
        reference operator*() const
		{
			return(_AVLtree::_getValue(_Ptr));
		};

		//class selection operator is mandatory in STL
        pointer operator->() const
		{
			//this is standard for STL
			return(_STD pointer_traits<pointer>::pointer_to(**this));
		}

		//get the node pointer
		_NodePtr _getnode(void)
		{
			return(_Ptr);
		}
		
		//this store the pointer to the element from the container by definition of the equivalence of the iterator
		_NodePtr _Ptr;
		_NodePtr _CurrentPtrLRR;
		stack<_NodePtr> _stackLRR;
    };
public:
	//typedefs of the real operator (those should be particular to each implementation
	//because they are templates they have to be particular to the classes
	typedef _iterator<AVLtree> iterator; //mutable operator
//	typedef _const_iterator<AVLtree> const_iterator; //constant iterator
	
	//reverse iterators optionals in STL
    typedef std::reverse_iterator<iterator> reverse_iterator; //optional
//    typedef std::reverse_iterator<const_iterator> const_reverse_iterator; //optional
	
	//rebind node necessary for allocators
	typename _Alloc::template rebind<_node>::other _Alnod;	// allocator object for nodes
public:
	AVLtree(){this->_headPtr=nullptr;_size=0;}
	~AVLtree(){clear();}
	void clear(void);
	void insert(_Tdata val){ _insert(val,this->_headPtr);}
	void remove(_Tdata val){ _remove(_findNode(val));}
	int getSize(void){ return this->_size;}
	iterator begin(void);
	iterator end(void);
	iterator find(_Tdata val);
	_Tdata getFirst(void);
	_Tdata getLast(void);
	_Tdata getPrevious(void);
	_Tdata getNext(void);
	_Tdata getHeadValue(void){if(this->_headPtr!=nullptr) return this->_headPtr->getValue();else return _Tdata(0);}
	int getHeadHeight(void){if(this->_headPtr!=nullptr) return this->_headPtr->getHeight(); else return 0;}
	bool setCurrentPosition(_Tdata val);
	void print_all(void){_print_all(this->_headPtr);}
	void runAllIntTest(void);
	std::vector<_Tdata> all_elements(void);
private:
	static reference _getValue(_NodePtr node){ return (reference)node->_value;}
	void _insert(_Tdata val,_NodePtr &nodePtr);
	void _print_all(_NodePtr top);
	void _LRR(std::vector<_Tdata> &vect,_NodePtr current);
	void _updateAllHeight(void);
	void _rotateRight(_NodePtr head);
	void _rotateLeft(_NodePtr head);
	void _restoreAVL(_NodePtr start,_NodePtr end);
	//those are needed for delete operation
	_NodePtr _findNode(_Tdata value);
	void _remove(_NodePtr nodeToDelete);
	void _updateBalanceToUp(_NodePtr start);
	_NodePtr _findMaxSubtree(_NodePtr start);
	_NodePtr _findMinSubtree(_NodePtr start);
	void _clear(_NodePtr current);
	//for getting data from tree
	_Tdata _getNextRightValue(_NodePtr start);
	_Tdata _getPreviousLeftValue(_NodePtr start);
	static _NodePtr _getPreviousLeftNode(_NodePtr start);
	static _NodePtr _PrevNode(_NodePtr pnode);
	static _NodePtr _getNextRightNode(_NodePtr start);
	static _NodePtr _NextNode(_NodePtr pnode);
	static _NodePtr _NextNodeOrder(stack<_NodePtr> &rstack,_Nodepref pCurrentNode);
	static _NodePtr _NextNodeOrderInit(_NodePtr head,_Nodepref pCurrentNodeLRR,_NodePtr pNode,stack<_NodePtr>& rstack);
	static _NodePtr _NextNodeOrderInit(_NodePtr head,_Nodepref pCurrentNodeLRR,_Tdata& rVal,stack<_NodePtr>& rstack);
};
/*----------------------------------------------------------------------
 * functions for the STL container operations
 *--------------------------------------------------------------------*/
//get the first element which is the most left element from tree which is the minimum
template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::iterator AVLtree<_Tdata,_Alloc>::begin(void)
{
	return iterator(_headPtr);
}

//return null ptr because this will be returned by _nextNode when it gets out of scope
template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::iterator AVLtree<_Tdata,_Alloc>::end(void)
{
	return iterator(nullptr,_headPtr);
}

template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::iterator AVLtree<_Tdata,_Alloc>::find(_Tdata val)
{
	return iterator(_headPtr,val);
}

/*---------------------------------------------------------------------------
 * functions for the AVL structure
 *-------------------------------------------------------------------------*/
// restore the AVL structue
template <class _Tdata, class _Alloc > void AVLtree<_Tdata,_Alloc>::_restoreAVL(_NodePtr start,_NodePtr end)
{
	_NodePtr _iteratorTmp;
	_NodePtr _stopParent;
	if(nullptr!=start) _stopParent=start->getParent();
	_iteratorTmp=end;
	if(nullptr==_iteratorTmp)
		return;
#ifdef DEBUG
	std::cout<<"start="<<start->getValue()<<" end="<<end->getValue()<<std::endl;
#endif
	while(nullptr!=_iteratorTmp && _iteratorTmp!=_stopParent)
	{
#ifdef DEBUG
	std::cout<<_iteratorTmp->getValue()<<" balance="<<_iteratorTmp->getBalance()<<std::endl;
#endif
		if(_iteratorTmp->getBalance()>1)
		{
#ifdef DEBUG
			std::cout<<"rotate left"<<std::endl;
#endif
			this->_rotateLeft(_iteratorTmp);
		}
		else if(_iteratorTmp->getBalance()<-1)
		{
#ifdef DEBUG
			std::cout<<"rotate right"<<std::endl;
#endif
			this->_rotateRight(_iteratorTmp);
		}
		_iteratorTmp=_iteratorTmp->getParent();
	}
	this->_headPtr->updateHeight();
}
/*
_rotateLeft
//	Perform a single rotation left about head.  This will rotate head's
//  parent to become head's left child.  Then head's left child will
//  become the former parent's right child.
*/
template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::_rotateLeft(_NodePtr head)
{
	_NodePtr temp=head->getRight();
	if(temp==nullptr)
		return;
	head->getRight()=temp->getLeft();
	if(temp->getLeft()!=nullptr)
		temp->getLeft()->getParent()=head;
	if(head->getParent()==nullptr)
	{
		this->_headPtr=temp;
		temp->getParent()=nullptr;
	}
	else if(head->getParent()->getLeft()==head)
	{
		head->getParent()->getLeft()=temp;
		temp->getParent()=head->getParent();
	}
	else
	{
		head->getParent()->getRight()=temp;
		temp->getParent()=head->getParent();
	}
	temp->getLeft()=head;
	head->getParent()=temp;
}
/*
//	Perform a single rotation right about head.  This will rotate head's
//   parent to become head's right child.  Then head's right child will
//   become the former parent's left child.
*/
 template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::_rotateRight(_NodePtr head)
{
	_NodePtr temp=head->getLeft();
	if(temp==nullptr)
		return;
	head->getLeft()=temp->getRight();
	if(temp->getRight()!=nullptr)
		temp->getRight()->getParent()=head;
	if(head->getParent()==nullptr)
	{
		this->_headPtr=temp;
		temp->getParent()=nullptr;
	}
	else if(head->getParent()->getRight()==head)
	{
		head->getParent()->getRight()=temp;
		temp->getParent()=head->getParent();
	}
	else
	{
		head->getParent()->getLeft()=temp;
		temp->getParent()=head->getParent();
	}
	temp->getRight()=head;
	head->getParent()=temp;
}

//function to update the height and balance for the nodes
template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::_updateAllHeight(void)
{
	this->_headPtr->updateHeight();
}
//function to insert the nodes
template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::_insert(_Tdata val,_NodePtr &nodePtr)
{
	if(nullptr==nodePtr)
	{
		nodePtr=new _node(val);
		this->_size=1;
		return;
	}
	_NodePtr _iteratorTmp;
	_iteratorTmp=nodePtr;
	_NodePtr _newNode;
	_NodePtr _outOfBalanceNode=nullptr;
	while(_iteratorTmp!=nullptr)
	{
		//if the value is already inserted then update the count
		if(_iteratorTmp->getValue()==val)
		{
			_iteratorTmp->setCount(_iteratorTmp->getCount()+1);
			return;
		}
		if(val<_iteratorTmp->getValue())
		{
			if(_iteratorTmp->getBalance()<0 && nullptr==_outOfBalanceNode)
				_outOfBalanceNode=_iteratorTmp;
			if(nullptr==_iteratorTmp->getLeft())
			{
				_newNode=new _node(val);
				this->_size++;
				_iteratorTmp->getLeft()=_newNode;
				break;
			}
			_iteratorTmp=_iteratorTmp->getLeft();
		}
		else
		{
			if(_iteratorTmp->getBalance()>0 && nullptr==_outOfBalanceNode)
				_outOfBalanceNode=_iteratorTmp;
			if(nullptr==_iteratorTmp->getRight())
			{
				_newNode=new _node(val);
				this->_size++;
				_iteratorTmp->getRight()=_newNode;
				break;
			}
			_iteratorTmp=_iteratorTmp->getRight();
		}
	}
	_newNode->getParent()=_iteratorTmp;
	this->_headPtr->updateHeight();
	if(nullptr!=_outOfBalanceNode)
	{
		this->_restoreAVL(_outOfBalanceNode,_newNode);
	}
	else
	{
#ifdef DEBUG
		std::cout<<"val="<<val<<" has parent="<<_iteratorTmp->getValue()<<std::endl;
#endif
		this->_restoreAVL(_iteratorTmp,_newNode);
	}
}

/*--------------------------------------------------------
functions needed for delete operation
--------------------------------------------------------*/
//function to find a node over the value
template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_findNode(_Tdata value)
{
	_NodePtr _temp=this->_headPtr;
	while(_temp!=nullptr)
	{
		if(value==_temp->getValue())
			return _temp;
		if(value<_temp->getValue())
			_temp=_temp->getLeft();
		else
			_temp=_temp->getRight();
	}
	return nullptr;
}

//function to find the maximum in a subtree
template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_findMaxSubtree(_NodePtr start)
{
	_NodePtr _temp=start;
	_NodePtr _iteratorTmp=start;
	_Tdata _max=start->getValue();
	while(_iteratorTmp!=nullptr)
	{
		if(_iteratorTmp->getValue()>_max)
		{
			_max=_iteratorTmp->getValue();
			_temp=_iteratorTmp;
		}
		_iteratorTmp=_iteratorTmp->getRight();
	}
	return _temp;
}

//function to find the minimum in a subtree
template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_findMinSubtree(_NodePtr start)
{
	_NodePtr _temp=start;
	_NodePtr _iteratorTmp=start;
	_Tdata _min=start->getValue();
	while(_iteratorTmp!=nullptr)
	{
		if(_iteratorTmp->getValue()<_min)
		{
			_min=_iteratorTmp->getValue();
			_temp=_iteratorTmp;
		}
		_iteratorTmp=_iteratorTmp->getLeft();
	}
	return _temp;
}

//function to update up the balance factors and height
template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::_updateBalanceToUp(_NodePtr start)
{
	_NodePtr _iteratorTmp=start;
	int lh; //left height
	int rh; //right height
	_iteratorTmp->updateHeight();
	_iteratorTmp=_iteratorTmp->getParent();
	while(_iteratorTmp!=nullptr)
	{
		if(_iteratorTmp->getLeft()!=nullptr)
			lh=_iteratorTmp->getLeft()->getHeight();
		else lh=0;
		if(_iteratorTmp->getRight()!=nullptr)
			rh=_iteratorTmp->getRight()->getHeight();
		else rh=0;
		_iteratorTmp->setBalance(rh-lh);
		if(rh>lh) _iteratorTmp->setHeight(rh+1);
		else _iteratorTmp->setHeight(lh+1);
		_iteratorTmp=_iteratorTmp->getParent();
	}
}

//function to remove an element
template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::_remove(_NodePtr nodeToDelete)
{
	_NodePtr _toInsertPtr=nullptr;
	_NodePtr _toInsertPtr1=nullptr;
	_NodePtr _parent;
	_NodePtr _toRealDelete=nodeToDelete;
	bool _gotoStep5;
	int _changedPos=0;
	//if it has one child or none
	//STEP 1
	_gotoStep5=false;
	if(nodeToDelete->getLeft()!=nullptr && nodeToDelete->getRight()==nullptr)
	{
		_toInsertPtr=nodeToDelete->getLeft();
		_gotoStep5=true;
	}
	else if(nodeToDelete->getRight()!=nullptr && nodeToDelete->getLeft()==nullptr)
	{
		_toInsertPtr=nodeToDelete->getRight();
		_gotoStep5=true;
	} if(nodeToDelete->getRight()==nullptr && nodeToDelete->getLeft()==nullptr)
	{
		_gotoStep5=true;
	}
	if(false==_gotoStep5)
	{
		_toInsertPtr=_findMaxSubtree(nodeToDelete->getLeft());
		_toInsertPtr1=_findMinSubtree(nodeToDelete->getRight());
		if(_toInsertPtr->getHeight()<_toInsertPtr1->getHeight())
		{
			_toInsertPtr=_toInsertPtr1;
			_changedPos=1;
		}
		else _changedPos=-1;
		_Tdata valueTmp;
		int countTmp;
		valueTmp=_toInsertPtr->getValue();
		countTmp=_toInsertPtr->getCount();
		_toInsertPtr->setCount(nodeToDelete->getCount());
		_toInsertPtr->setValue(nodeToDelete->getValue());
		nodeToDelete->setCount(countTmp);
		nodeToDelete->setValue(valueTmp);
		_toRealDelete=_toInsertPtr;
		if(_changedPos==-1) _toInsertPtr=_toInsertPtr->getLeft();
		else _toInsertPtr=_toInsertPtr->getRight();
	}
	//STEP 5
	//if it is the root
	if(_toRealDelete->getParent()==nullptr)
	{
		if(nullptr==_toInsertPtr)
		{
			this->_headPtr=nullptr;
		}
		else
		{
			this->_headPtr=_toInsertPtr;
			this->_headPtr->getParent()=nullptr;
		}
	}
	//insert the element to the parent
	else
	{
		_parent=_toRealDelete->getParent();
		if(_parent!=nodeToDelete)
		{
			//find the location where to put the info
			if(_toRealDelete->getValue()<_parent->getValue())
				_parent->getLeft()=_toInsertPtr;
			else
				_parent->getRight()=_toInsertPtr;
		}
		else
		{
			if(_toInsertPtr->getValue()<_parent->getValue())
				_parent->getLeft()=_toInsertPtr;
			else
				_parent->getRight()=_toInsertPtr;		}
	}
	//STEP 6
	this->_updateBalanceToUp(_parent);
	delete _toRealDelete;
	this->_size--;
	return;

}

/*--------------------------------------------------------
functions to get one element at a time
---------------------------------------------------------*/

//get the first element which is the most left element from tree which is the minimum
template <class _Tdata, class _Alloc> _Tdata AVLtree<_Tdata,_Alloc>::getFirst(void)
{
	_NodePtr _iteratorTmp=this->_headPtr;
	while(nullptr!=_iteratorTmp)
	{
		if(nullptr==_iteratorTmp->getLeft())
			return _iteratorTmp->getValue();
		_iteratorTmp=_iteratorTmp->getLeft();
	}
	return _Tdata(0);
}

//get the last element which is the most right element from tree which is the maximum
template <class _Tdata, class _Alloc> _Tdata AVLtree<_Tdata,_Alloc>::getLast(void)
{
	_NodePtr _iteratorTmp=this->_headPtr;
	while(nullptr!=_iteratorTmp)
	{
		if(nullptr==_iteratorTmp->getRight())
			return _iteratorTmp->getValue();
		_iteratorTmp=_iteratorTmp->getRight();
	}
	return _Tdata(0);
}

//this will set the internal position to a node
template <class _Tdata, class _Alloc> bool AVLtree<_Tdata,_Alloc>::setCurrentPosition(_Tdata val)
{
	this->_currentPosPtr=this->_findNode(val);
	if(nullptr!=this->_currentPosPtr) return true;
	else return false;
}

//get the next element on the right side
template <class _Tdata, class _Alloc> _Tdata AVLtree<_Tdata,_Alloc>::_getNextRightValue(_NodePtr start)
{
	_NodePtr _iteratorTmp;
	_NodePtr _parent=start;
	int _direction; //1 for up and -1 for down
	int _levels=1;
	int _rightWay=0;

	_iteratorTmp=_parent;
	++_levels;
	_parent=_iteratorTmp->getParent();
	if(nullptr==_parent)
	{
		return start->getRight()->getValue();
	}
	_direction=1;
	while(_levels>0)
	{
		if(1==_direction) //we go up to the root
		{
			if(_parent->getValue()<_iteratorTmp->getValue()) //it was on the right side
			{
				_iteratorTmp=_parent;
				_parent=_iteratorTmp->getParent();
				if(nullptr==_parent)
				{
					if(_direction==1)
					{
						if(_rightWay>=0) return start->getRight()->getValue();
					}
					_direction=-1;
					_rightWay=0;
				}
				else _direction=1;
				++_levels;
				++_rightWay;
			}
			else //it was on the left side
			{
				if(nullptr!=_parent->getRight()) //it has right child
				{
					_iteratorTmp=_parent->getRight();
					--_levels;
					_direction=-1;
					++_rightWay;
				}
				else
				{
					_iteratorTmp=_parent;
					_parent=_iteratorTmp->getParent();
					if(nullptr==_parent) _direction=-1;
					else _direction=1;
					++_levels;
					--_rightWay;
				}
			}
			continue;
		}
		if(-1==_direction) //we go down
		{
			if(nullptr!=_iteratorTmp->getLeft())
			{
				_parent=_iteratorTmp;
				_iteratorTmp=_parent->getLeft();
				--_levels;
				--_rightWay;
				continue;
			}
			if(nullptr!=_iteratorTmp->getRight())
			{
				_parent=_iteratorTmp;
				_iteratorTmp=_parent->getRight();
				--_levels;
				++_rightWay;
				continue;
			}
			_direction=1;
			_parent=_iteratorTmp->getParent();
			--_rightWay;
			++_levels;
		}
	}
	if(nullptr!=_iteratorTmp)
	{
		this->_currentPosPtr=_iteratorTmp;
		return _iteratorTmp->getValue();
	}
	return start->getRight()->getValue();
}

//get the next element at the same level
template <class _Tdata, class _Alloc> _Tdata AVLtree<_Tdata,_Alloc>::getNext(void)
{
	_NodePtr _parent;
	if(nullptr!=this->_currentPosPtr && this->_headPtr!=this->_currentPosPtr)
	{
		_parent=this->_currentPosPtr->getParent();
		if(this->_currentPosPtr->getValue()<_parent->getValue()) //it is left side
		{
			if(nullptr!=_parent->getRight()) //it has sibling
			{
				this->_currentPosPtr=_parent->getRight();
				return this->_currentPosPtr->getValue();
			}
			else //it has no sibling
				return this->_getNextRightValue(_parent);
		}
		else //it is on the right side
			return this->_getNextRightValue(_parent);
	}
	return this->_currentPosPtr->getValue();
}

//get the next element on the right side
template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_getNextRightNode(_NodePtr start)
{
	_NodePtr _iteratorTmp;
	_NodePtr _parent=start;
	int _direction; //1 for up and -1 for down
	int _levels=1;
	int _rightWay=0;

	_iteratorTmp=_parent;
	++_levels;
	_parent=_iteratorTmp->getParent();
	if(nullptr==_parent)
	{
		return nullptr;
	}
	_direction=1;
	while(_levels>0)
	{
		if(1==_direction) //we go up to the root
		{
			if(_parent->getValue()<_iteratorTmp->getValue()) //it was on the right side
			{
				_iteratorTmp=_parent;
				_parent=_iteratorTmp->getParent();
				if(nullptr==_parent)
				{
					if(_direction==1)
					{
						if(_rightWay>=0)
							return nullptr;
					}
					_direction=-1;
					_rightWay=0;
				}
				else _direction=1;
				++_levels;
				++_rightWay;
			}
			else //it was on the left side
			{
				if(nullptr!=_parent->getRight()) //it has right child
				{
					_iteratorTmp=_parent->getRight();
					--_levels;
					_direction=-1;
					++_rightWay;
				}
				else
				{
					_iteratorTmp=_parent;
					_parent=_iteratorTmp->getParent();
					if(nullptr==_parent) _direction=-1;
					else _direction=1;
					++_levels;
					--_rightWay;
				}
			}
			continue;
		}
		if(-1==_direction) //we go down
		{
			if(nullptr!=_iteratorTmp->getLeft())
			{
				_parent=_iteratorTmp;
				_iteratorTmp=_parent->getLeft();
				--_levels;
				--_rightWay;
				continue;
			}
			if(nullptr!=_iteratorTmp->getRight())
			{
				_parent=_iteratorTmp;
				_iteratorTmp=_parent->getRight();
				--_levels;
				++_rightWay;
				continue;
			}
			_direction=1;
			_parent=_iteratorTmp->getParent();
			++_levels;
			--_rightWay;
		}
	}
	if(nullptr!=_iteratorTmp)
	{
		return _iteratorTmp;
	}
	return nullptr;
}

template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_NextNode(_NodePtr pnode)
{
	_NodePtr _parent;
	if(nullptr!=pnode)
	{
		_parent=pnode->getParent();
		if(pnode->getValue()<_parent->getValue()) //it is left side
		{
			if(nullptr!=_parent->getRight()) //it has sibling
			{
				return _parent->getRight();
			}
			else //it has no sibling
				return _getNextRightNode(_parent);
		}
		else //it is on the right side
			return _getNextRightNode(_parent);
	}
	return pnode;
}
template <class _Tdata,class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_NextNodeOrderInit(_NodePtr phead,_Nodepref pCurrentNodeLRR,_NodePtr pNode,stack<_NodePtr>& rstack)
{
	_NodePtr retValue;
	pCurrentNodeLRR=phead->getLeft();
	rstack.push(phead);
	while(!(rstack.empty() && pCurrentNodeLRR==nullptr))
	{
		if(pCurrentNodeLRR==nullptr)
		{
			pCurrentNodeLRR=rstack.top();
			retValue=pCurrentNodeLRR;
			rstack.pop();
			pCurrentNodeLRR=pCurrentNodeLRR->getRight();
			return retValue;
		}
		else 
		{
			if (pCurrentNodeLRR==pNode)
			{				
				if(pCurrentNodeLRR->getRight()!=nullptr)
					pCurrentNodeLRR=pCurrentNodeLRR->getRight();
				else
					pCurrentNodeLRR=nullptr;
				return pNode;
			}
			else
			{
				rstack.push(pCurrentNodeLRR);
				pCurrentNodeLRR=pCurrentNodeLRR->getLeft();
			}
		}
	}
	return nullptr;
}
template <class _Tdata,class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_NextNodeOrderInit(_NodePtr phead,_Nodepref pCurrentNodeLRR,_Tdata& rVal,stack<_NodePtr>& rstack)
{
	_NodePtr retValue;
	pCurrentNodeLRR=phead->getLeft();
	rstack.push(phead);
	while(!(rstack.empty() && pCurrentNodeLRR==nullptr))
	{
		if(pCurrentNodeLRR==nullptr)
		{
			pCurrentNodeLRR=rstack.top();
			retValue=pCurrentNodeLRR;
			rstack.pop();
			pCurrentNodeLRR=pCurrentNodeLRR->getRight();
			return retValue;
		}
		else 
		{
			if (pCurrentNodeLRR->getValue()==rVal)
			{
				retValue=pCurrentNodeLRR;
				if(pCurrentNodeLRR->getRight()!=nullptr)
					pCurrentNodeLRR=pCurrentNodeLRR->getRight();
				else
					pCurrentNodeLRR=nullptr;
				return retValue;
			}
			else
			{
				rstack.push(pCurrentNodeLRR);
				pCurrentNodeLRR=pCurrentNodeLRR->getLeft();
			}
		}
	}
	return nullptr;
}
template <class _Tdata,class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_NextNodeOrder(stack<_NodePtr> &rstack,_Nodepref pCurrentNode)
{
	_NodePtr retValue;
	while(!(rstack.empty() && pCurrentNode==nullptr))
	{
		if(pCurrentNode==nullptr)
		{
			pCurrentNode=rstack.top();
			retValue=pCurrentNode;
			rstack.pop();
			pCurrentNode=pCurrentNode->getRight();
			return retValue;
		}
		else
		{
			rstack.push(pCurrentNode);
			pCurrentNode=pCurrentNode->getLeft();
		}
	}
	return nullptr;
}

template <class _Tdata, class _Alloc> _Tdata AVLtree<_Tdata,_Alloc>::_getPreviousLeftValue(_NodePtr start)
{
	_NodePtr _iteratorTmp;
	_NodePtr _parent=start;
	int _direction; //1 for up and -1 for down
	int _levels=1;
	int _rightWay=0;

	_iteratorTmp=_parent;
	++_levels;
	_parent=_iteratorTmp->getParent();
	if(nullptr==_parent)
	{
		return start->getLeft()->getValue();
	}
	_direction=1;
	while(_levels>0)
	{
		if(1==_direction) //we go up to the root
		{
			if(_parent->getValue()>_iteratorTmp->getValue()) //it was on the left side
			{
				_iteratorTmp=_parent;
				_parent=_iteratorTmp->getParent();
				if(nullptr==_parent)
				{
					if(_direction==1)
					{
						if(_rightWay>=0) return start->getLeft()->getValue();
					}
					_direction=-1;
					_rightWay=0;
				}
				else _direction=1;
				++_levels;
				++_rightWay;
			}
			else //it was on the right side
			{
				if(nullptr!=_parent->getLeft()) //it has left child
				{
					_iteratorTmp=_parent->getLeft();
					--_levels;
					_direction=-1;
					++_rightWay;
				}
				else
				{
					_iteratorTmp=_parent;
					_parent=_iteratorTmp->getParent();
					if(nullptr==_parent) _direction=-1;
					else _direction=1;
					++_levels;
					--_rightWay;
				}
			}
			continue;
		}
		if(-1==_direction) //we go down
		{
			if(nullptr!=_iteratorTmp->getRight())
			{
				_parent=_iteratorTmp;
				_iteratorTmp=_parent->getRight();
				--_levels;
				--_rightWay;
				continue;
			}
			if(nullptr!=_iteratorTmp->getLeft())
			{
				_parent=_iteratorTmp;
				_iteratorTmp=_parent->getLeft();
				--_levels;
				++_rightWay;
				continue;
			}
			_direction=1;
			_parent=_iteratorTmp->getParent();
			--_rightWay;
			++_levels;
		}
	}
	if(nullptr!=_iteratorTmp)
	{
		this->_currentPosPtr=_iteratorTmp;
		return _iteratorTmp->getValue();
	}
	return start->getLeft()->getValue();
}
//get the previous element on the same level
template <class _Tdata, class _Alloc> _Tdata AVLtree<_Tdata,_Alloc>::getPrevious(void)
{
	_NodePtr _parent;
	if(nullptr!=this->_currentPosPtr && this->_headPtr!=this->_currentPosPtr)
	{
		_parent=this->_currentPosPtr->getParent();
		if(this->_currentPosPtr->getValue()>_parent->getValue()) //it is right side
		{
			if(nullptr!=_parent->getLeft()) //it has sibling
			{
				this->_currentPosPtr=_parent->getLeft();
				return this->_currentPosPtr->getValue();
			}
			else //it has no sibling
				return this->_getPreviousLeftValue(_parent);
		}
		else
			return this->_getPreviousLeftValue(_parent);
	}
	return this->_currentPosPtr->getValue();
}

template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_getPreviousLeftNode(_NodePtr start)
{
	_NodePtr _iteratorTmp;
	_NodePtr _parent=start;
	int _direction; //1 for up and -1 for down
	int _levels=1;
	int _rightWay=0;

	_iteratorTmp=_parent;
	++_levels;
	_parent=_iteratorTmp->getParent();
	if(nullptr==_parent)
	{
		return nullptr;
	}
	_direction=1;
	while(_levels>0)
	{
		if(1==_direction) //we go up to the root
		{
			if(_parent->getValue()>_iteratorTmp->getValue()) //it was on the left side
			{
				_iteratorTmp=_parent;
				_parent=_iteratorTmp->getParent();
				if(nullptr==_parent)
				{
					if(_direction==1)
					{
						if(_rightWay>=0)
							return nullptr;
					}
					_direction=-1;
					_rightWay=0;
				}
				else _direction=1;
				++_levels;
				++_rightWay;
			}
			else //it was on the right side
			{
				if(nullptr!=_parent->getLeft()) //it has left child
				{
					_iteratorTmp=_parent->getLeft();
					--_levels;
					_direction=-1;
					++_rightWay;
				}
				else
				{
					_iteratorTmp=_parent;
					_parent=_iteratorTmp->getParent();
					if(nullptr==_parent) _direction=-1;
					else _direction=1;
					++_levels;
					--_rightWay;
				}
			}
			continue;
		}
		if(-1==_direction) //we go down
		{
			if(nullptr!=_iteratorTmp->getRight())
			{
				_parent=_iteratorTmp;
				_iteratorTmp=_parent->getRight();
				--_levels;
				--_rightWay;
				continue;
			}
			if(nullptr!=_iteratorTmp->getLeft())
			{
				_parent=_iteratorTmp;
				_iteratorTmp=_parent->getLeft();
				--_levels;
				++_rightWay;
				continue;
			}
			_direction=1;
			_parent=_iteratorTmp->getParent();
			--_rightWay;
			++_levels;
		}
	}
	if(nullptr!=_iteratorTmp)
	{
		return _iteratorTmp;
	}
	return nullptr;
}
//get the previous element on the same level
template <class _Tdata, class _Alloc> typename AVLtree<_Tdata,_Alloc>::_NodePtr AVLtree<_Tdata,_Alloc>::_PrevNode(_NodePtr pnode)
{
	_NodePtr _parent;
	if(nullptr!=pnode)
	{
		_parent=this->_currentPosPtr->getParent();
		if(pnode->getValue()>_parent->getValue()) //it is right side
		{
			if(nullptr!=_parent->getLeft()) //it has sibling
			{
				return _parent->getLeft();
			}
			else //it has no sibling
				return _getPreviousLeftNode(_parent);
		}
		else
			return _getPreviousLeftNode(_parent);
	}
	return pnode;
}
/*--------------------------------------------------------
functions to get all elements in sort order
--------------------------------------------------------*/

template <class _Tdata, class _Alloc> std::vector<_Tdata> AVLtree<_Tdata,_Alloc>::all_elements(void)
{
	std::vector<_Tdata> _outVector;
	this->_LRR(_outVector,this->_headPtr);
	return _outVector;
}

template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::_LRR(std::vector<_Tdata> &vect,_NodePtr current)
{
	if(nullptr!=current)
	{
		this->_LRR(vect,current->getLeft());
		vect.push_back(current->getValue());
		this->_LRR(vect,current->getRight());
	}
}

/*-----------------------------------------------------------
functions for cleanup
-----------------------------------------------------------*/

template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::clear(void)
{
	this->_clear(this->_headPtr);
	this->_headPtr=nullptr;
	this->_currentPosPtr=nullptr;
	this->_size=0;
}

template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::_clear(_NodePtr current)
{
	_NodePtr next;
	if(nullptr!=current)
	{
		this->_clear(current->getLeft());
		next=current->getRight();
		delete current;
		this->_clear(next);
	}
}


template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::runAllIntTest(void)
{
	 AVLtree_run_all_tests();
}

//function to print all elements + internal infor for the elements
template <class _Tdata, class _Alloc> void AVLtree<_Tdata,_Alloc>::_print_all(_NodePtr top)
{
	if(top!=nullptr)
	{
		this->_print_all(top->getLeft());
		std::cout<<top->getValue()<<" has count "<<top->getCount()<<" and has balance="<<top->getBalance()<<" and height="<<top->getHeight();
		if(top->getLeft()!=nullptr)
			std::cout<<" and son "<<(top->getLeft())->getValue();
		if(top->getRight()!=nullptr) 
			std::cout<<" and son "<<(top->getRight())->getValue();
		std::cout<<std::endl;
		std::cout.flush();
		this->_print_all(top->getRight());
	}
}

_STD_END