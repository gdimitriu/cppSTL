#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using std::vector;
//#define DEBUG 1
typedef int _Tname;
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
	typedef _node* _nodePtr;
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
	//for tests
	void _test1(void);
	void _test2(void);
};
