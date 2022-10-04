#pragma once
#include <string>

class Ccontainers
{
private:
	int count_wot(const std::string & s, char c);
	template <class C,class T> int count(const C& v,T val);
public:
	Ccontainers(void);
	~Ccontainers(void);
	void string_oper(void);
	int copyFile(void);
};

