#pragma once
#include<iostream>
#include<fstream>
#include <string>

class logImpl
{
public:
	logImpl();
	logImpl(std::string path);
	void setLoggerPath(std::string path);
	std::string getLoggerPath();
	void LogString(std::string str);
	~logImpl();
private:
	std::string sLoggerPath_;
	std::ofstream *pfFileStream_;
};
