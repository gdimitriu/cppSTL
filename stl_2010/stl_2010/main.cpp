#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include<iostream>
#include "gadiList_tests.h"
#include "avl_orig.h"
#include "AVLtree.h"
#include "map_assoc.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
//	run_tests();

//	avl_orig _avl;
//	_avl.run_tests();
//	AVLtree<int> *_avlTree=new AVLtree<int>;
//	_avlTree->runAllIntTest();
//	delete _avlTree;
	map_ssoc_run_all_unitests();
	_getch();
	return 0;
}