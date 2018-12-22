#include "StdAfx.h"
#include "Cex02_01.h"
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

Cex02_01::Cex02_01(void)
{
}


Cex02_01::~Cex02_01(void)
{
}


void Cex02_01::run(void)
{
	cout<<"Using reverse operation with a string"<<endl;
	string string1="mark twain";
	reverse(string1.begin(),string1.end());
	assert("niawt kram"==string1);
	cout<<"---- OK ----"<<endl;

	cout<<"Using reverse operation with an array"<<endl;
	char array1[]="mark twain";
	reverse(&array1[0],&array1[strlen(array1)]);
	assert("niawt kram"==string(array1));
	cout<<"---- OK ---- "<<endl;
}
