// kdl_singletons.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "displayImpl.h"
#include "keyboardImpl.h"
#include "logImpl.h"
#include "singleton_static.h"

void test_crash()
{
	keyboardImpl Keyboard;
	displayImpl Display;
	
	logImpl Logger("logger.log");
	
	Display.setLoggerDevice(&Logger);
	Keyboard.setLoggerDevice(&Logger);
	Keyboard.setString(std::string("here is the input"));
	Display.pushString(Keyboard.popString());
}

void test_dynamic_ok()
{
	logImpl *pLogger=new logImpl("logger.log");
	keyboardImpl *pKeyboard=new keyboardImpl(pLogger);
	displayImpl *pDisplay=new displayImpl(pLogger);

	pKeyboard->setString(std::string("here is the input"));
	pDisplay->pushString(pKeyboard->popString());

	delete pKeyboard;
	delete pDisplay;
	delete pLogger;
}

typedef singleton_static<logImpl> singletonLogger;

//logImpl* singletonLogger::pInternal_=nullptr;

typedef singleton_static<keyboardImpl> singletonKeyboard;

//keyboardImpl* singletonKeyboard::pInternal_=nullptr;

typedef singleton_static<displayImpl> singletonDisplay;

//displayImpl* singletonDisplay::pInternal_=nullptr;


void test_templates()
{
	singletonLogger::Instance().setLoggerPath("logger.log");
	singletonKeyboard::Instance().setLoggerDevice(&singletonLogger::Instance());
	singletonDisplay::Instance().setLoggerDevice(&singletonLogger::Instance());
	singletonKeyboard::Instance().setString(std::string("here is the input"));
	singletonDisplay::Instance().pushString(singletonKeyboard::Instance().popString());
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_templates();
	return 0;
}

