#include "displayImpl.h"
using std::string;

displayImpl::displayImpl()
{
	std::cout<<"display impl constructor\n";
	pLogger_=nullptr;
}

displayImpl::displayImpl(logImpl* logger)
{
	pLogger_=logger; //set the logger instance
	pLogger_->LogString(string("displayImpl constructor"));
}

displayImpl::~displayImpl()
{
	//do nothing for the logger instance
	//free of the logger pointer should be done externally due to dependencies
	pLogger_->LogString(string("displayImpl destructor"));
}

void displayImpl::setLoggerDevice(logImpl* logger)
{
	pLogger_=logger; //set the logger instance
	pLogger_->LogString(string("displayImpl setLoggerDevice"));
}

void displayImpl::pushString(std::string push)
{
	std::cout<<push<<std::endl;
}
