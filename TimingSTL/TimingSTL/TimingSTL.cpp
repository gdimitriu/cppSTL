// TimingSTL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FirstTiming.h"
#include "Second.h"

int _tmain(int argc, _TCHAR* argv[])
{
	FirstTiming *first;
	first=new FirstTiming;
	first->run();
	delete first;
	Second *second;
	second=new Second;
	second->run();
	delete second;
	return 0;
}

