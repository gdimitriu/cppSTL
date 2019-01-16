#include<iostream>
#include <vector>
#include <iterator>
using std::vector;

class CBaseWoPrototype
{
public:
	virtual void execute()=0;
};

class FirstWoP : public CBaseWoPrototype
{
public:
	void execute()
	{
		std::cout<<"Here is the first one"<<std::endl;
	}
};

class SecondWoP : public CBaseWoPrototype
{
public:
	void execute()
	{
		std::cout<<"Here is the second one"<<std::endl;
	}
};

class CBasePrototype
{
public:
	virtual CBasePrototype* clone()=0;
	virtual void execute()=0;
};

class FirstWP : public CBasePrototype
{
public:
	CBasePrototype* clone(){ return new FirstWP;}
	void execute()
	{
		std::cout<<"Here is the first one"<<std::endl;
	}
};

class SecondWP : public CBasePrototype
{
public:
	CBasePrototype* clone(){ return new SecondWP;}
	void execute()
	{
		std::cout<<"Here is the second one"<<std::endl;
	}
};

class FactoryBase
{
public:
	static CBasePrototype* make(int choice)
	{
		if(m_prototypes[choice]!=0)
			return m_prototypes[choice]->clone();
		else return 0;
	}
	static CBasePrototype* m_prototypes[3];
};

CBasePrototype* FactoryBase::m_prototypes[]={0,new FirstWP,new SecondWP};


int main()
{
	vector<CBaseWoPrototype *> rolesWoP;
	vector<CBasePrototype *> rolesWP;
	int choice;
	std::cout<<"First(1),Second(2),Go(0)"<<std::endl;
	while(1)
	{
		std::cin>>choice;
		if(choice==0)
			break;
		else if(choice==1)
		{
			rolesWP.push_back(FactoryBase::make(choice));
			rolesWoP.push_back(new FirstWoP);			
		}
		else
		{
			rolesWP.push_back(FactoryBase::make(choice));
			rolesWoP.push_back(new SecondWoP);
		}
	}
	for(vector<CBaseWoPrototype *>::iterator i=rolesWoP.begin();i!=rolesWoP.end();++i)
	{
		(*i)->execute();
	}
	for(vector<CBaseWoPrototype *>::iterator i=rolesWoP.begin();i!=rolesWoP.end();++i)
	{
		delete (*i);
	}
	std::cout<<"now the factory based"<<std::endl;
	for(vector<CBasePrototype *>::iterator i=rolesWP.begin();i!=rolesWP.end();++i)
	{
		(*i)->execute();
	}
	for(vector<CBasePrototype *>::iterator i=rolesWP.begin();i!=rolesWP.end();++i)
	{
		delete (*i);
	}
	std::cin>>choice;
}