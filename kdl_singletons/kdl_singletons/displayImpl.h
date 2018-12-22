#pragma once
#include <iostream>
#include <ostream>
#include "logImpl.h"

class displayImpl
{
public:
	displayImpl();
	displayImpl(logImpl* logger);
	~displayImpl();
	//set the logger device
	void setLoggerDevice(logImpl* logger);
	//push a string to the display device
	void pushString(std::string push);
private:
	logImpl *pLogger_; //pointer to the logger subsystem
};