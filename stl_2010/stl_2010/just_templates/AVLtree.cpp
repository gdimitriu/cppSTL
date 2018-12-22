#include "AVLtree.h"

/*--------------------------------------------------------
  functions for unitests
--------------------------------------------------------*/
//declaration for the test funtions

static void AVLtree_int_test1(void);
static void AVLtree_int_test2(void);


void AVLtree_run_all_tests(void)
{
	AVLtree_int_test1();
	AVLtree_int_test2();
}

static void AVLtree_int_test1(void)
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
	AVLtree<int> _AVL;

	for(std::vector<int>::iterator it=_tst.begin();it!=_tst.end();++it)
	{
		_AVL.insert(*it);
#ifdef DEBUG
		_print_all(_headPtr);
#endif
	}
	std::vector<int> _result=_AVL.all_elements();
	std::sort(_tst.begin(),_tst.end());
	for(std::vector<int>::iterator it=_tst.begin(),itrez=_result.begin();it!=_tst.end();++it,++itrez)
	{
		assert(*it==*itrez);
	}
	std::cout<<"end AVLtree::run_tests"<<std::endl;
	std::cout<<"head is " <<_AVL.getHeadValue()<<" and has height="<<_AVL.getHeadHeight()<<std::endl;
	_AVL.print_all();
	std::cout<<"starting to remove elements"<<std::endl;
	_AVL.remove(45);
	std::cout<<"head is " <<_AVL.getHeadValue()<<" and has height="<<_AVL.getHeadHeight()<<std::endl;
	_AVL.print_all();
	std::cout<<"end remove elements"<<std::endl;
	_AVL.clear();
}


static void AVLtree_int_test2(void)
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
	AVLtree<int> _AVL;

	for(std::vector<int>::iterator it=_tst.begin();it!=_tst.end();++it)
	{
		_AVL.insert(*it);
#ifdef DEBUG
		_print_all(_headPtr);
#endif
	}
	std::vector<int> _result=_AVL.all_elements();
	std::sort(_tst.begin(),_tst.end());
	for(std::vector<int>::iterator it=_tst.begin(),itrez=_result.begin();it!=_tst.end();++it,++itrez)
	{
		assert(*it==*itrez);
	}
	std::cout<<"end AVLtree::run_tests"<<std::endl;
	std::cout<<"head is " <<_AVL.getHeadValue()<<" and has height="<<_AVL.getHeadHeight()<<std::endl;
	_AVL.print_all();
	std::cout<<"start getting data"<<std::endl;
	std::cout<<"now testing next"<<std::endl;
	_AVL.setCurrentPosition(7);
	assert(12==_AVL.getNext());
	assert(7==_AVL.getPrevious());
	assert(7==_AVL.getFirst());
	assert(76==_AVL.getLast());
	_AVL.setCurrentPosition(19);
	assert(54==_AVL.getNext());
	_AVL.setCurrentPosition(23);
	assert(76==_AVL.getNext());
	std::cout<<"now testing previous"<<std::endl;
	_AVL.setCurrentPosition(72);
	assert(54==_AVL.getPrevious());
	assert(19==_AVL.getPrevious());
	_AVL.setCurrentPosition(76);
	assert(23==_AVL.getPrevious());
	std::cout<<"end getting data"<<std::endl;
	std::cout<<"starting to remove elements"<<std::endl;
	_AVL.remove(67);
	std::cout<<"head is " <<_AVL.getHeadValue()<<" and has height="<<_AVL.getHeadHeight()<<std::endl;
	_AVL.print_all();
	std::cout<<"end remove elements"<<std::endl;
	_AVL.remove(12);
	_AVL.setCurrentPosition(7);
	assert(17==_AVL.getNext());
	_AVL.clear();
}

