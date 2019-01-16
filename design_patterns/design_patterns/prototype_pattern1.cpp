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

//class for factory
class CPrototypeFactory
{
public:
	CPrototype * Create(int index)
	{
		if(index<m_pPrototypes.size())
			if(m_pPrototypes[index]!=nullptr)
				return m_pPrototypes[index]->Clone();
		return nullptr;
	}
	CPrototype * GetPrototype(int index)
	{
		if(index<m_pPrototypes.size())
			return m_pPrototypes[index];
		return nullptr;
	}
	void SetPrototype(CPrototype *proto,int index)
	{
		if(m_pPrototypes.size()<index+1)
		{
			m_pPrototypes.resize(index+1);
		}
		m_pPrototypes[index]=proto;
	}
	int GetNumberOfPrototypes() const
	{
		return m_pPrototypes.size();
	}
protected:
	std::vector<CPrototype*> m_pPrototypes;
};

//first class
class CFirst : public CPrototype
{
public:
	CFirst()
	{
		m_iValue=0;
	}
	CPrototype* Clone()
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
class CSecond : public CPrototype
{
public:
	CSecond()
	{
		m_sStr="execute ";
		m_iInternal=0;
	}
	CPrototype* Clone()
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
	std::string m_sStr;
	int m_iInternal;
};

int main(void)
{
	list<CPrototype *> lp;
	int choose;
	CPrototypeFactory cPF;
	cPF.SetPrototype(nullptr,0);
	cPF.SetPrototype(new CSecond,2);
	cPF.SetPrototype(new CFirst,1);	
/*	std::cout<<"Input First(1),Second(2),Go(0)"<<std::endl;
	while(1)
	{
		std::cin>>choose;
		if(choose==0)
			break;
		lp.push_back(cPF.Create(choose));
	}*/
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
	std::cin>>choose;
}