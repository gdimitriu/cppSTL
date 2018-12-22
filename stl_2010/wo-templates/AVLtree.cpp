#include "AVLtree.h"

/*--------------------------------------------------------
  functions for unitests
--------------------------------------------------------*/

void AVLtree::runAllIntTest(void)
{
	_test1();
	_test2();
}

//function to print all elements + internal infor for the elements
void AVLtree::_print_all(_nodePtr top)
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

void AVLtree::_test1(void)
{
	std::cout<<"start AVLtree::run_tests"<<std::endl;
	std::vector<int> _tst;
	_tst.push_back(50);
	_tst.push_back(40);
	_tst.push_back(30);
	_tst.push_back(35);
	_tst.push_back(37);
	_tst.push_back(39);
	_tst.push_back(45);
	_tst.push_back(55);
	_tst.push_back(42);

	for(std::vector<int>::iterator it=_tst.begin();it!=_tst.end();++it)
	{
		insert(*it);
#ifdef DEBUG
		_print_all(_headPtr);
#endif
	}
	std::vector<int> _result=all_elements();
	std::sort(_tst.begin(),_tst.end());
	for(std::vector<int>::iterator it=_tst.begin(),itrez=_result.begin();it!=_tst.end();++it,++itrez)
	{
		assert(*it==*itrez);
	}
	std::cout<<"end AVLtree::run_tests"<<std::endl;
	std::cout<<"head is " <<_headPtr->getValue()<<" and has height="<<_headPtr->getHeight()<<std::endl;
	_print_all(_headPtr);
	std::cout<<"starting to remove elements"<<std::endl;
	remove(45);
	std::cout<<"head is " <<_headPtr->getValue()<<" and has height="<<_headPtr->getHeight()<<std::endl;
	_print_all(_headPtr);
	std::cout<<"end remove elements"<<std::endl;
	clear();
}


void AVLtree::_test2(void)
{
	std::cout<<"start AVLtree::run_tests"<<std::endl;
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

	for(std::vector<int>::iterator it=_tst.begin();it!=_tst.end();++it)
	{
		insert(*it);
#ifdef DEBUG
		_print_all(_headPtr);
#endif
	}
	std::vector<int> _result=all_elements();
	std::sort(_tst.begin(),_tst.end());
	for(std::vector<int>::iterator it=_tst.begin(),itrez=_result.begin();it!=_tst.end();++it,++itrez)
	{
		assert(*it==*itrez);
	}
	std::cout<<"end AVLtree::run_tests"<<std::endl;
	std::cout<<"head is " <<_headPtr->getValue()<<" and has height="<<_headPtr->getHeight()<<std::endl;
	_print_all(_headPtr);
	std::cout<<"start getting data"<<std::endl;
	std::cout<<"now testing next"<<std::endl;
	setCurrentPosition(7);
	assert(12==getNext());
	assert(7==getPrevious());
	assert(7==getFirst());
	assert(76==getLast());
	setCurrentPosition(19);
	assert(54==getNext());
	setCurrentPosition(23);
	assert(76==getNext());
	std::cout<<"now testing previous"<<std::endl;
	setCurrentPosition(72);
	assert(54==getPrevious());
	assert(19==getPrevious());
	setCurrentPosition(76);
	assert(23==getPrevious());
	std::cout<<"end getting data"<<std::endl;
	std::cout<<"starting to remove elements"<<std::endl;
	remove(67);
	std::cout<<"head is " <<_headPtr->getValue()<<" and has height="<<_headPtr->getHeight()<<std::endl;
	_print_all(_headPtr);
	std::cout<<"end remove elements"<<std::endl;
	remove(12);
	setCurrentPosition(7);
	assert(17==getNext());
	clear();
}

/*--------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
those will be moved to .h when it will be transformed in template
----------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------*/

// restore the AVL structue
void AVLtree::_restoreAVL(_nodePtr start,_nodePtr end)
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
void AVLtree::_rotateLeft(_nodePtr head)
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
 void AVLtree::_rotateRight(_nodePtr head)
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
void AVLtree::_updateAllHeight(void)
{
	_headPtr->updateHeight();
}
//function to insert the nodes
void AVLtree::_insert(_Tname val,_nodePtr &nodePtr)
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
AVLtree::_nodePtr AVLtree::_findNode(_Tname value)
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
AVLtree::_nodePtr AVLtree::_findMaxSubtree(_nodePtr start)
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
AVLtree::_nodePtr AVLtree::_findMinSubtree(_nodePtr start)
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
void AVLtree::_updateBalanceToUp(_nodePtr start)
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
void AVLtree::_remove(_nodePtr nodeToDelete)
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
_Tname AVLtree::getFirst(void)
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
_Tname AVLtree::getLast(void)
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
bool AVLtree::setCurrentPosition(_Tname val)
{
	_currentPosPtr=_findNode(val);
	if(nullptr!=_currentPosPtr) return true;
	else return false;
}

//get the next element on the right side
_Tname AVLtree::_getNextRight(_nodePtr start)
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
_Tname AVLtree::getNext(void)
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

_Tname AVLtree::_getPreviousLeft(_nodePtr start)
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
_Tname AVLtree::getPrevious(void)
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

std::vector<_Tname> AVLtree::all_elements(void)
{
	std::vector<_Tname> _outVector;
	_LRR(_outVector,_headPtr);
	return _outVector;
}

void AVLtree::_LRR(std::vector<_Tname> &vect,_nodePtr current)
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

void AVLtree::clear(void)
{
	_clear(_headPtr);
	_headPtr=nullptr;
	_currentPosPtr=nullptr;
	_size=0;
}

void AVLtree::_clear(_nodePtr current)
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
