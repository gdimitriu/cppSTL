#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<sstream>

using std::string;
using std::vector;
using std::list;

//pure virtual class for the prototype
class CPrototype
{
public:
	virtual CPrototype* Clone()=0;
	virtual void execute(int val)=0;
	virtual void print(void)=0;
};

//first class
template <class base>
class CFirst : public  base
{
public:
	CFirst()
	{
		m_iValue=0;
	}
	base * Clone()
	{
		return new CFirst;
	}
	void execute(int val=0)
	{
		m_iValue+=val;
	}
	void print(void)
	{
		std::cout<<"execute first with value "<<m_iValue<<std::endl;
	}
protected:
	int m_iValue;
};

//second class
template <class base>
class CSecond : public base
{
public:
	CSecond()
	{
		m_sStr="execute ";
		m_iInternal=0;
	}
	base* Clone()
	{
		return new CSecond;
	}
	void execute(int val=0)
	{
		m_sStr="executed ";
		std::ostringstream oss;
		oss<<val;
		m_iInternal+=val;
		m_sStr+=oss.str();
	}
	void print(void)
	{
		std::cout<<m_sStr<<"\t"<<m_iInternal<<std::endl;
	}
protected:
	string m_sStr;
	int m_iInternal;
};

//class for factory
template<class ToCreate>
class CPrototypeFactory
{
public:
	ToCreate * Create(int index)
	{
		if(static_cast<unsigned int>(index)<m_pPrototypes.size())
			if(m_pPrototypes[index]!=nullptr)
				return m_pPrototypes[index]->Clone();
		return nullptr;
	}
	ToCreate * GetPrototype(int index)
	{
		if(static_cast<unsigned int>(index)<m_pPrototypes.size())
			return m_pPrototypes[index];
		return nullptr;
	}
	void SetPrototype(ToCreate *proto,int index)
	{
		if(m_pPrototypes.size()<static_cast<unsigned int>(index)+1)
		{
			m_pPrototypes.resize(index+1);
		}
		m_pPrototypes[index]=proto;
	}
	int GetNumberOfPrototypes() const
	{
		return m_pPrototypes.size();
	}
	CPrototypeFactory()
	{
	}
	~CPrototypeFactory()
	{
		vector<ToCreate*>::iterator it;
		for(it=m_pPrototypes.begin();it!=m_pPrototypes.end();++it)
			delete *it;
	}
protected:
	vector<ToCreate*> m_pPrototypes;
};

template<class ToCreate>
class CPrototypeFactoryOne
{
public:
	ToCreate * Create(void)
	{
		if(m_pPrototype!=nullptr)
			return dynamic_cast<ToCreate *>(m_pPrototype->Clone());
		return nullptr;
	}
	void SetPrototype(ToCreate *proto)
	{
		m_pPrototype=proto;
	}
	ToCreate* GetPrototype(void)
	{
		return m_pPrototype;
	}
	CPrototypeFactoryOne(){m_pPrototype=nullptr;}
	~CPrototypeFactoryOne()
	{
		delete m_pPrototype;
	}
protected:
	ToCreate* m_pPrototype;
};

template<class ToCreate>
class CNewFactoryOne
{
public:
	ToCreate* Create(void)
	{
		return new ToCreate;
	}
};

void unitestCPrototypeFactory(void)
{
	list<CPrototype *> lp;
	CPrototypeFactory<CPrototype> cPF;
	
	std::cout<<"Prototypes all creation\n";
	
	cPF.SetPrototype(nullptr,0);
	cPF.SetPrototype(new CSecond<CPrototype>,2);
	cPF.SetPrototype(new CFirst<CPrototype>,1);	

	lp.push_back(cPF.Create(1));
	lp.push_back(cPF.Create(2));
	lp.push_back(cPF.Create(1));
	lp.push_back(cPF.Create(2));
	lp.push_back(cPF.Create(2));
	int pos=0;
	list<CPrototype *>::iterator it;
	for(it=lp.begin();it!=lp.end();++it,++pos)
	{
		(*it)->execute(pos);
	}
	for(it=lp.begin();it!=lp.end();++it)
		(*it)->print();
	pos=0;
	for(it=lp.begin();it!=lp.end();++it,++pos)
	{
		(*it)->execute(-pos);
	}
	std::cout<<"after substracting"<<std::endl;
	for(it=lp.begin();it!=lp.end();++it)
		(*it)->print();
	for(it=lp.begin();it!=lp.end();++it)
	{
		delete (*it);
	}
}

void unitestPrototypeFactoryOne(void)
{
	list<CPrototype *> lp;	
	int pos=0;
	list<CPrototype *>::iterator it;

	std::cout<<"Prototype one creation\n";
	CPrototypeFactoryOne<CFirst<CPrototype>> FirstFactory;
	CPrototypeFactoryOne<CSecond<CPrototype>> SecondFactory;
	FirstFactory.SetPrototype(new CFirst<CPrototype>);
	SecondFactory.SetPrototype(new CSecond<CPrototype>);
	lp.push_back(FirstFactory.Create());
	lp.push_back(SecondFactory.Create());
	lp.push_back(FirstFactory.Create());
	lp.push_back(SecondFactory.Create());
	lp.push_back(SecondFactory.Create());
	
	pos=0;
	for(it=lp.begin();it!=lp.end();++it,++pos)
	{
		(*it)->execute(pos);
	}
	for(it=lp.begin();it!=lp.end();++it)
		(*it)->print();
	pos=0;
	for(it=lp.begin();it!=lp.end();++it,++pos)
	{
		(*it)->execute(-pos);
	}
	std::cout<<"after substracting"<<std::endl;
	for(it=lp.begin();it!=lp.end();++it)
		(*it)->print();
	for(it=lp.begin();it!=lp.end();++it)
	{
		delete (*it);
	}
}

void unitestNewFactoryOne(void)
{
	list<CPrototype *> lp;	
	int pos=0;
	list<CPrototype *>::iterator it;

	std::cout<<"New creation\n";

	CNewFactoryOne<CFirst<CPrototype>> FirstFactory;
	CNewFactoryOne<CSecond<CPrototype>> SecondFactory;
	lp.push_back(FirstFactory.Create());
	lp.push_back(SecondFactory.Create());
	lp.push_back(FirstFactory.Create());
	lp.push_back(SecondFactory.Create());
	lp.push_back(SecondFactory.Create());

	pos=0;
	for(it=lp.begin();it!=lp.end();++it,++pos)
	{
		(*it)->execute(pos);
	}
	for(it=lp.begin();it!=lp.end();++it)
		(*it)->print();
	pos=0;
	for(it=lp.begin();it!=lp.end();++it,++pos)
	{
		(*it)->execute(-pos);
	}
	std::cout<<"after substracting"<<std::endl;
	for(it=lp.begin();it!=lp.end();++it)
		(*it)->print();
	for(it=lp.begin();it!=lp.end();++it)
	{
		delete (*it);
	}
}


template <template <class T> class Policy,class ToCreate,class base=ToCreate> class CFactoryManager : public Policy<base>
{
public:
	void SwitchPrototype(base *proto)
	{
		Policy<base> & myPolicy=*this;
		delete myPolicy.GetPrototype();
		myPolicy.SetPrototype(proto);
	};
};


void unitestFactoryPolicy(void)
{
	list<CPrototype *> lp;	
	int pos=0;
	list<CPrototype *>::iterator it;

	std::cout<<"New policy creation\n";

	CFactoryManager<CNewFactoryOne,CFirst<CPrototype>> FirstFactory;
	CFactoryManager<CPrototypeFactoryOne,CSecond<CPrototype>,CPrototype> SecondFactory;
	SecondFactory.SetPrototype(new CSecond<CPrototype>);
	lp.push_back(FirstFactory.Create());
	lp.push_back(SecondFactory.Create());
	lp.push_back(FirstFactory.Create());
	lp.push_back(SecondFactory.Create());
	lp.push_back(SecondFactory.Create());

	pos=0;
	for(it=lp.begin();it!=lp.end();++it,++pos)
	{
		(*it)->execute(pos);
	}
	for(it=lp.begin();it!=lp.end();++it)
		(*it)->print();
	pos=0;
	for(it=lp.begin();it!=lp.end();++it,++pos)
	{
		(*it)->execute(-pos);
	}
	CFirst<CPrototype> *tmp=new CFirst<CPrototype>(*(dynamic_cast<CFirst<CPrototype> *>(*(lp.begin()))));
	SecondFactory.SwitchPrototype(tmp);
	lp.push_back(SecondFactory.Create());
	std::cout<<"after substracting"<<std::endl;
	for(it=lp.begin();it!=lp.end();++it)
		(*it)->print();
	for(it=lp.begin();it!=lp.end();++it)
	{
		delete (*it);
	}
}
int main(void)
{
	int choose;
	
	unitestCPrototypeFactory();

	unitestPrototypeFactoryOne();

	unitestNewFactoryOne();

	std::cout<<"Policies now to create\n";
	
	unitestFactoryPolicy();
	
	std::cin>>choose;
}