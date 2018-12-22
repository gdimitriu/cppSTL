#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using std::vector;
//#define DEBUG 1
//for unitests
void AVLtree_run_all_tests(void);

template<typename _Tname>
class AVLtree
{
private:
	class _node
	{
	private:
		_Tname _value;
		int _height;
		int _balance;
		int _count;
		_node *_left;
		_node *_right;
		_node *_parent;
	public:
		_node(_Tname val):_value(val)
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
		_Tname getValue(){ return _value;}
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
		void setValue(_Tname val) {_value=val;}
		void setLeft(_node *val){_left=val;}
		void setRight(_node *val){_right=val;}
		void setParent(_node *val){_parent=val;}
	};
public:
	typedef typename _node* _nodePtr;
private:
	_nodePtr _headPtr;
	int _size;
	_nodePtr _currentPosPtr;
public:
	AVLtree(){_headPtr=nullptr;_size=0;}
	~AVLtree(){clear();}
	void clear(void);
	void insert(_Tname val){ _insert(val,_headPtr);}
	void remove(_Tname val){ _remove(_findNode(val));}
	int getSize(void){ return _size;}
	_Tname getFirst(void);
	_Tname getLast(void);
	_Tname getPrevious(void);
	_Tname getNext(void);
	_Tname getHeadValue(void){if(_headPtr!=nullptr) return _headPtr->getValue();else return _Tname(0);}
	int getHeadHeight(void){if(_headPtr!=nullptr) return _headPtr->getHeight(); else return 0;}
	bool setCurrentPosition(_Tname val);
	void print_all(void){_print_all(_headPtr);}
	void runAllIntTest(void);
	std::vector<_Tname> all_elements(void);
private:
	void _insert(_Tname val,_nodePtr &nodePtr);
	void _print_all(_nodePtr top);
	void _LRR(std::vector<_Tname> &vect,_nodePtr current);
	void _updateAllHeight(void);
	void _rotateRight(_nodePtr head);
	void _rotateLeft(_nodePtr head);
	void _restoreAVL(_nodePtr start,_nodePtr end);
	//those are needed for delete operation
	_nodePtr _findNode(_Tname value);
	void _remove(_nodePtr nodeToDelete);
	void _updateBalanceToUp(_nodePtr start);
	_nodePtr _findMaxSubtree(_nodePtr start);
	_nodePtr _findMinSubtree(_nodePtr start);
	void _clear(_nodePtr current);
	//for getting data from tree
	_Tname _getNextRight(_nodePtr start);
	_Tname _getPreviousLeft(_nodePtr start);
};

// restore the AVL structue
template<typename _Tname> void AVLtree<_Tname>::_restoreAVL(_nodePtr start,_nodePtr end)
{
	_nodePtr _iterator;
	_nodePtr _stopParent;
	if(nullptr!=start) _stopParent=start->getParent();
	_iterator=end;
	if(nullptr==_iterator)
		return;
#ifdef DEBUG
	std::cout<<"start="<<start->getValue()<<" end="<<end->getValue()<<std::endl;
#endif
	while(nullptr!=_iterator && _iterator!=_stopParent)
	{
#ifdef DEBUG
	std::cout<<_iterator->getValue()<<" balance="<<_iterator->getBalance()<<std::endl;
#endif
		if(_iterator->getBalance()>1)
		{
#ifdef DEBUG
			std::cout<<"rotate left"<<std::endl;
#endif
			_rotateLeft(_iterator);
		}
		else if(_iterator->getBalance()<-1)
		{
#ifdef DEBUG
			std::cout<<"rotate right"<<std::endl;
#endif
			_rotateRight(_iterator);
		}
		_iterator=_iterator->getParent();
	}
	_headPtr->updateHeight();
}
/*
_rotateLeft
//	Perform a single rotation left about head.  This will rotate head's
//  parent to become head's left child.  Then head's left child will
//  become the former parent's right child.
*/
template<typename _Tname> void AVLtree<_Tname>::_rotateLeft(_nodePtr head)
{
	_nodePtr temp=head->getRight();
	if(temp==nullptr)
		return;
	head->getRight()=temp->getLeft();
	if(temp->getLeft()!=nullptr)
		temp->getLeft()->getParent()=head;
	if(head->getParent()==nullptr)
	{
		_headPtr=temp;
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
 template<typename _Tname> void AVLtree<_Tname>::_rotateRight(_nodePtr head)
{
	_nodePtr temp=head->getLeft();
	if(temp==nullptr)
		return;
	head->getLeft()=temp->getRight();
	if(temp->getRight()!=nullptr)
		temp->getRight()->getParent()=head;
	if(head->getParent()==nullptr)
	{
		_headPtr=temp;
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
template<typename _Tname> void AVLtree<_Tname>::_updateAllHeight(void)
{
	_headPtr->updateHeight();
}
//function to insert the nodes
template<typename _Tname> void AVLtree<_Tname>::_insert(_Tname val,_nodePtr &nodePtr)
{
	if(nullptr==nodePtr)
	{
		nodePtr=new _node(val);
		_size=1;
		return;
	}
	_nodePtr _iterator;
	_iterator=nodePtr;
	_nodePtr _newNode;
	_nodePtr _outOfBalanceNode=nullptr;
	while(_iterator!=nullptr)
	{
		//if the value is already inserted then update the count
		if(_iterator->getValue()==val)
		{
			_iterator->setCount(_iterator->getCount()+1);
			return;
		}
		if(val<_iterator->getValue())
		{
			if(_iterator->getBalance()<0 && nullptr==_outOfBalanceNode)
				_outOfBalanceNode=_iterator;
			if(nullptr==_iterator->getLeft())
			{
				_newNode=new _node(val);
				++_size;
				_iterator->getLeft()=_newNode;
				break;
			}
			_iterator=_iterator->getLeft();
		}
		else
		{
			if(_iterator->getBalance()>0 && nullptr==_outOfBalanceNode)
				_outOfBalanceNode=_iterator;
			if(nullptr==_iterator->getRight())
			{
				_newNode=new _node(val);
				++_size;
				_iterator->getRight()=_newNode;
				break;
			}
			_iterator=_iterator->getRight();
		}
	}
	_newNode->getParent()=_iterator;
	_headPtr->updateHeight();
	if(nullptr!=_outOfBalanceNode)
	{
		_restoreAVL(_outOfBalanceNode,_newNode);
	}
	else
	{
#ifdef DEBUG
		std::cout<<"val="<<val<<" has parent="<<_iterator->getValue()<<std::endl;
#endif
		_restoreAVL(_iterator,_newNode);
	}
}

/*--------------------------------------------------------
functions needed for delete operation
--------------------------------------------------------*/
//function to find a node over the value
template<typename _Tname> typename AVLtree<_Tname>::_nodePtr AVLtree<_Tname>::_findNode(_Tname value)
{
	_nodePtr _temp=_headPtr;
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
template<typename _Tname> typename AVLtree<_Tname>::_nodePtr AVLtree<_Tname>::_findMaxSubtree(_nodePtr start)
{
	_nodePtr _temp=start;
	_nodePtr _iterator=start;
	_Tname _max=start->getValue();
	while(_iterator!=nullptr)
	{
		if(_iterator->getValue()>_max)
		{
			_max=_iterator->getValue();
			_temp=_iterator;
		}
		_iterator=_iterator->getRight();
	}
	return _temp;
}

//function to find the minimum in a subtree
template<typename _Tname> typename AVLtree<_Tname>::_nodePtr AVLtree<_Tname>::_findMinSubtree(_nodePtr start)
{
	_nodePtr _temp=start;
	_nodePtr _iterator=start;
	_Tname _min=start->getValue();
	while(_iterator!=nullptr)
	{
		if(_iterator->getValue()<_min)
		{
			_min=_iterator->getValue();
			_temp=_iterator;
		}
		_iterator=_iterator->getLeft();
	}
	return _temp;
}

//function to update up the balance factors and height
template<typename _Tname> void AVLtree<_Tname>::_updateBalanceToUp(_nodePtr start)
{
	_nodePtr _iterator=start;
	int lh; //left height
	int rh; //right height
	_iterator->updateHeight();
	_iterator=_iterator->getParent();
	while(_iterator!=nullptr)
	{
		if(_iterator->getLeft()!=nullptr)
			lh=_iterator->getLeft()->getHeight();
		else lh=0;
		if(_iterator->getRight()!=nullptr)
			rh=_iterator->getRight()->getHeight();
		else rh=0;
		_iterator->setBalance(rh-lh);
		if(rh>lh) _iterator->setHeight(rh+1);
		else _iterator->setHeight(lh+1);
		_iterator=_iterator->getParent();
	}
}

//function to remove an element
template<typename _Tname> void AVLtree<_Tname>::_remove(_nodePtr nodeToDelete)
{
	_nodePtr _toInsertPtr=nullptr;
	_nodePtr _toInsertPtr1=nullptr;
	_nodePtr _parent;
	_nodePtr _toRealDelete=nodeToDelete;
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
		_Tname valueTmp;
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
			_headPtr=nullptr;
		}
		else
		{
			_headPtr=_toInsertPtr;
			_headPtr->getParent()=nullptr;
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
	_updateBalanceToUp(_parent);
	delete _toRealDelete;
	--_size;
	return;

}

/*--------------------------------------------------------
functions to get one element at a time
---------------------------------------------------------*/

//get the first element which is the most left element from tree which is the minimum
template<typename _Tname> _Tname AVLtree<_Tname>::getFirst(void)
{
	_nodePtr _iterator=_headPtr;
	while(nullptr!=_iterator)
	{
		if(nullptr==_iterator->getLeft())
			return _iterator->getValue();
		_iterator=_iterator->getLeft();
	}
	return _Tname(0);
}

//get the last element which is the most right element from tree which is the maximum
template<typename _Tname> _Tname AVLtree<_Tname>::getLast(void)
{
	_nodePtr _iterator=_headPtr;
	while(nullptr!=_iterator)
	{
		if(nullptr==_iterator->getRight())
			return _iterator->getValue();
		_iterator=_iterator->getRight();
	}
	return _Tname(0);
}

//this will set the internal position to a node
template<typename _Tname> bool AVLtree<_Tname>::setCurrentPosition(_Tname val)
{
	_currentPosPtr=_findNode(val);
	if(nullptr!=_currentPosPtr) return true;
	else return false;
}

//get the next element on the right side
template<typename _Tname> _Tname AVLtree<_Tname>::_getNextRight(_nodePtr start)
{
	_nodePtr _iterator;
	_nodePtr _parent=start;
	int _direction; //1 for up and -1 for down
	int _levels=1;

	_iterator=_parent;
	++_levels;
	_parent=_iterator->getParent();
	_direction=1;
	while(_levels>0)
	{
		if(1==_direction) //we go up to the root
		{
			if(_parent->getValue()<_iterator->getValue()) //it was on the right side
			{
				_iterator=_parent;
				_parent=_iterator->getParent();
				if(nullptr==_parent) _direction=-1;
				else _direction=1;
				++_levels;
			}
			else //it was on the left side
			{
				if(nullptr!=_parent->getRight()) //it has right child
				{
					_iterator=_parent->getRight();
					--_levels;
					_direction=-1;
				}
				else
				{
					_iterator=_parent;
					_parent=_iterator->getParent();
					if(nullptr==_parent) _direction=-1;
					else _direction=1;
					++_levels;
				}
			}
			continue;
		}
		if(-1==_direction) //we go down
		{
			if(nullptr!=_iterator->getLeft())
			{
				_parent=_iterator;
				_iterator=_parent->getLeft();
				--_levels;
				continue;
			}
			if(nullptr!=_iterator->getRight())
			{
				_parent=_iterator;
				_iterator=_parent->getRight();
				--_levels;
				continue;
			}
			_direction=1;
			_parent=_iterator->getParent();
			++_levels;
		}
	}
	if(nullptr!=_iterator)
	{
		_currentPosPtr=_iterator;
		return _iterator->getValue();
	}
	return _Tname(0);
}

//get the next element at the same level
template<typename _Tname> _Tname AVLtree<_Tname>::getNext(void)
{
	_nodePtr _parent;
	if(nullptr!=_currentPosPtr && _headPtr!=_currentPosPtr)
	{
		_parent=_currentPosPtr->getParent();
		if(_currentPosPtr->getValue()<_parent->getValue()) //it is left side
		{
			if(nullptr!=_parent->getRight()) //it has sibling
			{
				_currentPosPtr=_parent->getRight();
				return _currentPosPtr->getValue();
			}
			else //it has no sibling
				return _getNextRight(_parent);
		}
		else //it is on the right side
			return _getNextRight(_parent);
	}
	return _Tname(0);
}

template<typename _Tname> _Tname AVLtree<_Tname>::_getPreviousLeft(_nodePtr start)
{
	_nodePtr _iterator;
	_nodePtr _parent=start;
	int _direction; //1 for up and -1 for down
	int _levels=1;

	_iterator=_parent;
	++_levels;
	_parent=_iterator->getParent();
	_direction=1;
	while(_levels>0)
	{
		if(1==_direction) //we go up to the root
		{
			if(_parent->getValue()>_iterator->getValue()) //it was on the left side
			{
				_iterator=_parent;
				_parent=_iterator->getParent();
				if(nullptr==_parent) _direction=-1;
				else _direction=1;
				++_levels;
			}
			else //it was on the right side
			{
				if(nullptr!=_parent->getLeft()) //it has left child
				{
					_iterator=_parent->getLeft();
					--_levels;
					_direction=-1;
				}
				else
				{
					_iterator=_parent;
					_parent=_iterator->getParent();
					if(nullptr==_parent) _direction=-1;
					else _direction=1;
					++_levels;
				}
			}
			continue;
		}
		if(-1==_direction) //we go down
		{
			if(nullptr!=_iterator->getRight())
			{
				_parent=_iterator;
				_iterator=_parent->getRight();
				--_levels;
				continue;
			}
			if(nullptr!=_iterator->getLeft())
			{
				_parent=_iterator;
				_iterator=_parent->getLeft();
				--_levels;
				continue;
			}
			_direction=1;
			_parent=_iterator->getParent();
			++_levels;
		}
	}
	if(nullptr!=_iterator)
	{
		_currentPosPtr=_iterator;
		return _iterator->getValue();
	}
	return _Tname(0);
}
//get the previous element on the same level
template<typename _Tname> _Tname AVLtree<_Tname>::getPrevious(void)
{
	_nodePtr _parent;
	if(nullptr!=_currentPosPtr && _headPtr!=_currentPosPtr)
	{
		_parent=_currentPosPtr->getParent();
		if(_currentPosPtr->getValue()>_parent->getValue()) //it is right side
		{
			if(nullptr!=_parent->getLeft()) //it has sibling
			{
				_currentPosPtr=_parent->getLeft();
				return _currentPosPtr->getValue();
			}
			else //it has no sibling
				return _getPreviousLeft(_parent);
		}
		else
			return _getPreviousLeft(_parent);
	}
	return _Tname(0);
}
/*--------------------------------------------------------
functions to get all elements in sort order
--------------------------------------------------------*/

template<typename _Tname> std::vector<_Tname> AVLtree<_Tname>::all_elements(void)
{
	std::vector<_Tname> _outVector;
	_LRR(_outVector,_headPtr);
	return _outVector;
}

template<typename _Tname> void AVLtree<_Tname>::_LRR(std::vector<_Tname> &vect,_nodePtr current)
{
	if(nullptr!=current)
	{
		_LRR(vect,current->getLeft());
		vect.push_back(current->getValue());
		_LRR(vect,current->getRight());
	}
}

/*-----------------------------------------------------------
functions for cleanup
-----------------------------------------------------------*/

template<typename _Tname> void AVLtree<_Tname>::clear(void)
{
	_clear(_headPtr);
	_headPtr=nullptr;
	_currentPosPtr=nullptr;
	_size=0;
}

template<typename _Tname> void AVLtree<_Tname>::_clear(_nodePtr current)
{
	_nodePtr next;
	if(nullptr!=current)
	{
		_clear(current->getLeft());
		next=current->getRight();
		delete current;
		_clear(next);
	}
}


template<typename _Tname> void AVLtree<_Tname>::runAllIntTest(void)
{
	 AVLtree_run_all_tests();
}

//function to print all elements + internal infor for the elements
template<typename _Tname> void AVLtree<_Tname>::_print_all(_nodePtr top)
{
	if(top!=nullptr)
	{
		_print_all(top->getLeft());
		std::cout<<top->getValue()<<" has count "<<top->getCount()<<" and has balance="<<top->getBalance()<<" and height="<<top->getHeight();
		if(top->getLeft()!=nullptr)
			std::cout<<" and son "<<(top->getLeft())->getValue();
		if(top->getRight()!=nullptr) 
			std::cout<<" and son "<<(top->getRight())->getValue();
		std::cout<<std::endl;
		std::cout.flush();
		_print_all(top->getRight());
	}
}