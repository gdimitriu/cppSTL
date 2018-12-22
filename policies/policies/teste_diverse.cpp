#include <iostream>
#include <string>
using std::string;

class element
{
public:
	virtual void Set(string &val)=0;
	virtual void Print(void)=0;
};

class eFirst: public element
{
	string m_sMessage;
public:
	void Set(string &val){m_sMessage=val;};
	void Print(void){ std::cout<<m_sMessage<<std::endl;
};

class eSecond : public element
{
	string m_sMessage;
public:
	void Set(string &val){m_sMessage=val;};
	void Print(void){ std::cout<<m_sMessage<<std::endl;
};

class eThird : public element
{
public:
};

//class for widget factory
class ElementsFactory
{
public:
	virtual eFirst *CreateFirst()=0;
	virtual eSecond *CreateSecond()=0;
	virtual eThird *CreateThird()=0;
};

template<class T>
T *MakeElement(ElementsFactory &factory)
{
	T * pw=factory.Create<T>();
	return pw;
}
int main(void)
{
	//

	//wait for a key
	char blocked;
	std::cin>>blocked;
}
