#include "keyboardImpl.h"

using std::string;

keyboardImpl::keyboardImpl()
{
	std::cout<<"keyboardImpl constructor\n";
	pLogger_=nullptr;
	sBuffer_.clear();
}

keyboardImpl::keyboardImpl(logImpl* logger)
{
	pLogger_=logger; //assign the logger instance
	sBuffer_.clear(); //clear the keyboard buffer
	pLogger_->LogString(string("keyboardImpl constructor"));
}

keyboardImpl::~keyboardImpl()
{
	//do nothing for the logger instnace
	//free of the logger pointer should be done externally due to dependencies
	pLogger_->LogString(string("keyboardImpl destructor"));
}

void keyboardImpl::setLoggerDevice(logImpl* logger)
{
	pLogger_=logger;
	pLogger_->LogString(string("keyboardImpl setLoggerDevice"));
}

//this will return the string buffer of the console
std::string keyboardImpl::popString(void)
{
	return sBuffer_;
}

//this is used for unitests to simulate the keyboard typing
void keyboardImpl::setString(std::string& str)
{
	sBuffer_.swap(str);
}