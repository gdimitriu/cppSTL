#include <vector>
#include <algorithm>
#include <cassert>

using std::vector;
#pragma once


template <typename _Tname>
class tree_class
{
private:
	class _node;
public:
	typedef typename _node * _nodePtr;
private:
	class _node
	{
	public:
		_Tname _value;
		int _balance;
		int _count;
		_nodePtr _left;
		_nodePtr _right;
		_nodePtr _parent;
		_node(_Tname val): _value(val)
		{
			_balance=0;
			_count=1;
			_left=nullptr;
			_right=nullptr;
			_parent=nullptr;
		};
		_Tname getValue(void) { return _value;};
	};
	_nodePtr _headPtr;
public:
	void insert(_Tname val);
	tree_class()
	{
		_headPtr=nullptr;
	}
	std::vector<_Tname> all_elements(void);
	void run_tests(void);
	void print_all(void);
	bool remove(_Tname val);
private:
	void _insert(_Tname val,_nodePtr &nodePtr);
	void _LRR(std::vector<_Tname> &vect,_nodePtr current);
	void _restoreAVL(_nodePtr outOfBalanceNode,_nodePtr newNode);
	void _adjustBalanceFactors(_nodePtr end,_nodePtr start);
	void _adjustBalanceFactorsRightLeft(_nodePtr end,_nodePtr start);
	void _adjustBalanceFactorsLeftRight(_nodePtr end,_nodePtr start);
	void _rotateLeft(_nodePtr head);
	void _rotateRight(_nodePtr head);
	void _print_all(_nodePtr head);
	//those are needed for remove function
	_nodePtr _findNode(_Tname &value);
	void _restoreAVLremove(_nodePtr outOfBalanceNode,_nodePtr newNode);
	void _adjustBalanceFactorsRemove(_nodePtr end,_nodePtr start);
	void _adjustBalanceFactorsRightLeftRemove(_nodePtr end,_nodePtr start);
	void _adjustBalanceFactorsLeftRightRemove(_nodePtr end,_nodePtr start);
};

template<typename _Tname> void tree_class<_Tname>::insert(_Tname val)
{
	_insert(val,_headPtr);
}

/*
_rotateLeft
//	Perform a single rotation left about head.  This will rotate head's
//  parent to become head's left child.  Then head's left child will
//  become the former parent's right child.
*/
template<typename _Tname> void tree_class<_Tname>::_rotateLeft(_nodePtr head)
{
	_nodePtr temp=head->_right;
	if(temp==nullptr)
		return;
	head->_right=temp->_left;
	if(temp->_left!=nullptr)
		temp->_left->_parent=head;
	if(head->_parent==nullptr)
	{
		_headPtr=temp;
		temp->_parent=nullptr;
	}
	else if(head->_parent->_left==head)
	{
		head->_parent->_left=temp;
		temp->_parent=head->_parent;
	}
	else
	{
		head->_parent->_right=temp;
		temp->_parent=head->_parent;
	}
	temp->_left=head;
	head->_parent=temp;
}
/*
//	Perform a single rotation right about head.  This will rotate head's
//   parent to become head's right child.  Then head's right child will
//   become the former parent's left child.
*/
template<typename _Tname> void tree_class<_Tname>::_rotateRight(_nodePtr head)
{
	_nodePtr temp=head->_left;
	if(temp==nullptr)
		return;
	head->_left=temp->_right;
	if(temp->_right!=nullptr)
		temp->_right->_parent=head;
	if(head->_parent==nullptr)
	{
		_headPtr=temp;
		temp->_parent=nullptr;
	}
	else if(head->_parent->_right==head)
	{
		head->_parent->_right=temp;
		temp->_parent=head->_parent;
	}
	else
	{
		head->_parent->_left=temp;
		temp->_parent=head->_parent;
	}
	temp->_right=head;
	head->_parent=temp;
}
template<typename _Tname> void tree_class<_Tname>::_insert(_Tname val,_nodePtr &nodePtr)
{
	if(nullptr==nodePtr)
	{
		nodePtr=new _node(val);
		return;
	}
	_nodePtr _iterator;
	_iterator=nodePtr;
	_nodePtr _newNode=new _node(val);
	_nodePtr _outOfBalanceNode=nullptr;
	while(_iterator!=nullptr)
	{
		//mark the node which will be out of balance
		if(0!=_iterator->_balance)
			_outOfBalanceNode=_iterator;
		//if the value is already inserted then update the count
		if(_iterator->getValue()==val)
		{
			_iterator->_count++;
			return;
		}
		if(val<_iterator->getValue())
		{
			if(nullptr==_iterator->_left)
			{
				_iterator->_left=_newNode;
				break;
			}
			_iterator=_iterator->_left;
		}
		else
		{
			if(nullptr==_iterator->_right)
			{
				_iterator->_right=_newNode;
				break;
			}
			_iterator=_iterator->_right;
		}
	}
	_newNode->_parent=_iterator;
	_restoreAVL(_outOfBalanceNode,_newNode);
}

template<typename _Tname> void tree_class<_Tname>::_restoreAVL(_nodePtr outOfBalanceNode,_nodePtr newNode)
{
	//outOfBalanceNode is null
	if(outOfBalanceNode==nullptr)
	{
		if(newNode->getValue()<_headPtr->getValue())
			_headPtr->_balance=-1;
		else
			_headPtr->_balance=1;
		_adjustBalanceFactors(_headPtr,newNode);
	}
	// the outOfBalanceNode will be balanced
	else if((1==outOfBalanceNode->_balance && newNode->getValue()<outOfBalanceNode->getValue()) || (-1==outOfBalanceNode->_balance && newNode->getValue()>outOfBalanceNode->getValue()))
	{
		outOfBalanceNode->_balance=0;
		_adjustBalanceFactors(outOfBalanceNode,newNode);
	}
	//the outofbalancenode was already right balanced and insertion into the right so rotate left
	else if((1==outOfBalanceNode->_balance) && (outOfBalanceNode->_right->getValue()<newNode->getValue()))
	{
		outOfBalanceNode->_balance=0;
		_rotateLeft(outOfBalanceNode);
		_adjustBalanceFactors(outOfBalanceNode->_parent,newNode);
	}
	//the outofbalancenode was already left balanced and insertion into the left so rotate right
	else if((-1==outOfBalanceNode->_balance) && (outOfBalanceNode->_left->getValue()>newNode->getValue()))
	{
		outOfBalanceNode->_balance=0;
		_rotateRight(outOfBalanceNode);
		_adjustBalanceFactors(outOfBalanceNode->_parent,newNode);
	}
	else if((outOfBalanceNode->_balance == -1) && (newNode->getValue() > outOfBalanceNode->_left->getValue()))
    {
		_rotateLeft(outOfBalanceNode->_left);
		_rotateRight(outOfBalanceNode);
		_adjustBalanceFactorsLeftRight(outOfBalanceNode,newNode);
   }
	else
    {
      // Perform double left rotation (actually a right followed by a left)
		_rotateRight(outOfBalanceNode->_right);
        _rotateLeft(outOfBalanceNode);
        _adjustBalanceFactorsRightLeft(outOfBalanceNode, newNode);
    }
}

template<typename _Tname> void tree_class<_Tname>::_adjustBalanceFactors(_nodePtr end,_nodePtr start)
{
	_nodePtr temp=start->_parent;
	while(temp!=end)
	{
		if(start->getValue()<temp->getValue())
			temp->_balance=-1;
		else
			temp->_balance=1;
		temp=temp->_parent;
	}
}

template<typename _Tname> void tree_class<_Tname>::_adjustBalanceFactorsRightLeft(_nodePtr end,_nodePtr start)
{
	if(end==_headPtr)
		end->_balance=0;
	else if(start->getValue()>end->_parent->getValue())
	{
		end->_balance=-1;
		_adjustBalanceFactors(end->_parent->_right,start);
	}
	else
	{
		end->_balance=0;
		end->_parent->_right->_balance=1;
		_adjustBalanceFactors(end,start);
	}
}

template<typename _Tname> void tree_class<_Tname>::_adjustBalanceFactorsLeftRight(_nodePtr end,_nodePtr start)
{
	if(end==_headPtr)
		end->_balance=0;
	else if(start->getValue()<end->_parent->getValue())
	{
		end->_balance=1;
		_adjustBalanceFactors(end->_parent->_left,start);
	}
	else
	{
		end->_balance=0;
		end->_parent->_left->_balance=-1;
		_adjustBalanceFactors(end,start);
	}
}

template<typename _Tname> std::vector<_Tname> tree_class<_Tname>::all_elements(void)
{
	std::vector<_Tname> _outVector;
	_LRR(_outVector,_headPtr);
	return _outVector;
}

template<typename _Tname> void tree_class<_Tname>::_LRR(std::vector<_Tname> &vect,_nodePtr current)
{
	if(nullptr!=current)
	{
		_LRR(vect,current->_left);
		vect.push_back(current->getValue());
		_LRR(vect,current->_right);
	}
}

template<typename _Tname> typename tree_class<_Tname>::_nodePtr tree_class<_Tname>::_findNode(_Tname &value)
{
	_nodePtr temp;
	temp=_headPtr;
	while(temp!=nullptr)
	{
		if(temp->getValue()==value)
			return temp;
		if(temp->getValue()<value)
			temp=temp->_right;
		else temp=temp->_left;
	}
	return (_nodePtr)(nullptr);
}

template<typename _Tname> bool tree_class<_Tname>::remove(_Tname val)
{
	if(_headPtr==nullptr)
		return false;
	_nodePtr _node_to_remove=_findNode(val);
	if(_node_to_remove==nullptr)
		return false;
	if(--_node_to_remove->_count>0)
		return true;
	_nodePtr _parent=_node_to_remove->_parent;
	_nodePtr _replacement;
	_nodePtr _outOfBalance;
	_nodePtr _replacement_parent;
	_nodePtr _node_moved;
	int _position;
	if(_parent!=nullptr)
	{
		if(_parent->_left==_node_to_remove) _position=-1;
		else _position=1;
	}
	int _balance=_node_to_remove->_balance;
	if((_node_to_remove->_left==nullptr) && (_node_to_remove->_right==nullptr))
	{
		if(_parent!=nullptr)
		{
			if(_position==-1) _parent->_left=nullptr;
			else _parent->_right=nullptr;
			//balance again
//			_restoreAVLremove(_parent,_node_to_remove);
			delete _node_to_remove;
		}
		else
		{
			_headPtr=nullptr;
			delete _node_to_remove;
		}
	}
	else
	{
		if(_balance>0)
		{
			if(_node_to_remove->_left->_right==nullptr)
			{
				_replacement=_node_to_remove->_left;
				_replacement->_right=_node_to_remove->_right;
				_outOfBalance=_replacement;
				_node_moved=_node_to_remove->_right;
			}
			else
			{
				_replacement=_node_to_remove->_left->_right;
				while(_replacement->_right!=nullptr)
				{
					_replacement=_replacement->_right;
				}
				_replacement_parent=_replacement->_parent;
				_replacement_parent->_right=_replacement->_left;
				_outOfBalance=_replacement_parent;
				_replacement->_left=_node_to_remove->_left;
				_replacement->_right=_node_to_remove->_right;
			}
		}
		else
		{
			if(_node_to_remove->_right->_left==nullptr)
			{
				_replacement=_node_to_remove->_right;
				_replacement->_left=_node_to_remove->_left;
				_outOfBalance=_replacement;
				_node_moved=_node_to_remove->_left;
				return true;
			}
			else
			{
				_replacement=_node_to_remove->_right->_left;
				while(_replacement->_left!=nullptr)
				{
					_replacement=_replacement->_left;
				}
				_replacement_parent=_replacement->_parent;
				_replacement_parent->_left=_replacement->_right;
				_outOfBalance=_replacement_parent;
				_replacement->_left=_node_to_remove->_left;
				_replacement->_right=_node_to_remove->_right;
				_node_to_remove->_left=_node_to_remove->_right=nullptr;
			}
		}
		if(_parent!=nullptr)
		{
			if(_position==-1) _parent->_left=_replacement;
			else _parent->_right=_replacement;
		}
		else
		{
			_headPtr=_replacement;
			_replacement->_parent=nullptr;
		}
//		_restoreAVLremove(_outOfBalance,_node_moved);
		delete _node_to_remove;
	}
	return true;
}


template<typename _Tname> void tree_class<_Tname>::_restoreAVLremove(_nodePtr outOfBalanceNode,_nodePtr newNode)
{
	//outOfBalanceNode is null
	if(outOfBalanceNode==nullptr)
	{
		if(newNode->getValue()<_headPtr->getValue())
			_headPtr->_balance=-1;
		else
			_headPtr->_balance=1;
		_adjustBalanceFactorsRemove(_headPtr,newNode);
	}
	// the outOfBalanceNode will be balanced
	else if((1==outOfBalanceNode->_balance && newNode->getValue()<outOfBalanceNode->getValue()) || (-1==outOfBalanceNode->_balance && newNode->getValue()>outOfBalanceNode->getValue()))
	{
		outOfBalanceNode->_balance=0;
		_adjustBalanceFactorsRemove(outOfBalanceNode,newNode);
	}
	//the outofbalancenode was already right balanced and insertion into the right so rotate left
	else if((1==outOfBalanceNode->_balance) && (outOfBalanceNode->_right->getValue()<newNode->getValue()))
	{
		outOfBalanceNode->_balance=0;
		_rotateLeft(outOfBalanceNode);
		_adjustBalanceFactorsRemove(outOfBalanceNode->_parent,newNode);
	}
	//the outofbalancenode was already left balanced and insertion into the left so rotate right
	else if((-1==outOfBalanceNode->_balance) && (outOfBalanceNode->_left->getValue()>newNode->getValue()))
	{
		outOfBalanceNode->_balance=0;
		_rotateRight(outOfBalanceNode);
		_adjustBalanceFactorsRemove(outOfBalanceNode->_parent,newNode);
	}
	else if((outOfBalanceNode->_balance == -1) && (newNode->getValue() > outOfBalanceNode->_left->getValue()))
    {
		_rotateLeft(outOfBalanceNode->_left);
		_rotateRight(outOfBalanceNode);
		_adjustBalanceFactorsLeftRightRemove(outOfBalanceNode,newNode);
   }
	else
    {
      // Perform double left rotation (actually a right followed by a left)
		_rotateRight(outOfBalanceNode->_right);
        _rotateLeft(outOfBalanceNode);
        _adjustBalanceFactorsRightLeftRemove(outOfBalanceNode, newNode);
    }
}

template<typename _Tname> void tree_class<_Tname>::_adjustBalanceFactorsRemove(_nodePtr end,_nodePtr start)
{
	_nodePtr temp=start->_parent;
	while(temp!=end)
	{
		if(start->getValue()<temp->getValue())
			temp->_balance=-1;
		else
			temp->_balance=1;
		temp=temp->_parent;
	}
}

template<typename _Tname> void tree_class<_Tname>::_adjustBalanceFactorsRightLeftRemove(_nodePtr end,_nodePtr start)
{
	if(end==_headPtr)
		end->_balance=0;
	else if(start->getValue()>end->_parent->getValue())
	{
		end->_balance=-1;
		_adjustBalanceFactorsRemove(end->_parent->_right,start);
	}
	else
	{
		end->_balance=0;
		end->_parent->_right->_balance=1;
		_adjustBalanceFactorsRemove(end,start);
	}
}

template<typename _Tname> void tree_class<_Tname>::_adjustBalanceFactorsLeftRightRemove(_nodePtr end,_nodePtr start)
{
	if(end==_headPtr)
		end->_balance=0;
	else if(start->getValue()<end->_parent->getValue())
	{
		end->_balance=1;
		_adjustBalanceFactorsRemove(end->_parent->_left,start);
	}
	else
	{
		end->_balance=0;
		end->_parent->_left->_balance=-1;
		_adjustBalanceFactorsRemove(end,start);
	}
}


template<typename _Tname> void tree_class<_Tname>::run_tests(void)
{
	std::cout<<"start tree_class::run_tests"<<std::endl;
	std::vector<_Tname> _tst;
/*	_tst.push_back(50);
	_tst.push_back(40);
	_tst.push_back(30);
	_tst.push_back(35);
	_tst.push_back(37);
	_tst.push_back(39);
	_tst.push_back(45);
	_tst.push_back(55);
	_tst.push_back(42);
	*/
	_tst.push_back(9);
	_tst.push_back(12);
	_tst.push_back(14);
	_tst.push_back(17);
	_tst.push_back(23);
	_tst.push_back(19);
	_tst.push_back(50);
	_tst.push_back(72);
	_tst.push_back(54);
	_tst.push_back(67);
	_tst.push_back(76);
	for(std::vector<_Tname>::iterator it=_tst.begin();it!=_tst.end();++it)
	{
		insert(*it);
	}
	std::vector<_Tname> _result=all_elements();
	std::sort(_tst.begin(),_tst.end());
	for(std::vector<_Tname>::iterator it=_tst.begin(),itrez=_result.begin();it!=_tst.end();++it,++itrez)
	{
		assert(*it==*itrez);
	}
	std::cout<<"end tree_class::run_tests"<<std::endl;
	print_all();
	std::cout<<"starting to remove elements"<<std::endl;
//	remove(45);
	print_all();
	std::cout<<"end removing elements"<<std::endl;
}

template<typename _Tname> void tree_class<_Tname>::print_all(void)
{
	_print_all(_headPtr);
}

template<typename _Tname> void tree_class<_Tname>::_print_all(_nodePtr top) //afisare leg arbori
{
	if(top!=nullptr)
	{
		_print_all(top->_left);
		std::cout<<top->_value<<" de "<<top->_count<<" ori si are bal="<<top->_balance;
		if(top->_left!=nullptr)
			std::cout<<" si fiul "<<(top->_left)->_value;
		if(top->_right!=nullptr) 
			std::cout<<" si fiul "<<(top->_right)->_value;
		std::cout<<std::endl;
		std::cout.flush();
		_print_all(top->_right);
	}
}
