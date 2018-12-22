#pragma once
class Cpair_objects
{
public:
	int first;
	char second;
public:
	Cpair_objects(int x,char y): first(x), second(y){}
	Cpair_objects(void);
	~Cpair_objects(void);
};

template <typename T1,typename T2>
class Cpair
{
public:
	T1 first;
	T2 second;
	Cpair(): first(T1()),second(T2()){}
	Cpair(const T1 &x,const T2 &y): first(x), second (y){}
};

template <typename T> const T& max_template(T &x,T &y)
{
	if(x<y)
		return y;
	else 
		return x;
}
