#pragma once
#include<iostream>
#include <string>
#include "logImpl.h"

class keyboardImpl
{
public:
	keyboardImpl();
	keyboardImpl(logImpl* logger);
	~keyboardImpl();
	//set the logger device
	void setLoggerDevice(logImpl* logger);
	//get the input string from the keyboard internal buffer
	std::string popString(void);
	//set the string for unitests
	void setString(std::string& str);
private:
	logImpl* pLogger_; //pointer to the logger subsystem
	std::string sBuffer_; //internal buffer
};
