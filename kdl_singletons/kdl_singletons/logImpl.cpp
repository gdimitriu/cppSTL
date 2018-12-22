#include "logImpl.h"

logImpl::logImpl()
{
	pfFileStream_=new std::ofstream;
	std::cout<<"logImpl constructor\n";
}

logImpl::logImpl(std::string path) :sLoggerPath_(path)
{
	pfFileStream_=new std::ofstream;
	pfFileStream_->open(sLoggerPath_);
}

logImpl::~logImpl()
{
	if(pfFileStream_->is_open())
	{
		(*pfFileStream_)<<"logImpl destructor\n";
		pfFileStream_->close();
	}
	delete pfFileStream_;
	std::cout<<"logImpl destructor\n";
}

//setters and gethers of the logger path file
void logImpl::setLoggerPath(std::string path)
{
	//close the old stream
	if(pfFileStream_->is_open())
		pfFileStream_->close();
	//set the new stream
	sLoggerPath_=path;
	//reopen the stream
	pfFileStream_->open(sLoggerPath_);
}

std::string logImpl::getLoggerPath()
{
	return sLoggerPath_;
}

void logImpl::LogString(std::string str)
{
	(*pfFileStream_)<<str<<std::endl;
}