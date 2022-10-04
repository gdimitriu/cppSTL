// std_libs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Cunit_conversion.h"
#include "Cstd_libs.h"
#include "Ccontainers.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//unit conversion class
	Cunit_conversion unit;
	unit.run();
	//diffrent in/out and stdlibs
	Cstd_libs stdlib;
//	stdlib.run_inout();

	//work with containers
	Ccontainers container;
//	container.string_oper();
//	container.copyFile();
	container.add_erase();
	return 0;
}

