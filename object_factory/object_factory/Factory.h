#pragma once
#include<map>

template<class AbstractObject, typename IdentifierType,typename ProductCreator=AbstractObject* (*)()>
class Factory
{
public:
	bool RegisterCreator(IdentifierType id,ProductCreator creator)
	{
		return AssociationMap_.insert(AssociationsMap::value_type(id,creator)).second;
	}
	bool UnRegisterCreator(IdentifierType id)
	{
		return AssociationMap_.erase(id).second;
	}
	AbstractObject* CreateObject(IdentifierType& id)
	{
		typename AssociationsMap::const_iterator it=AssociationMap_.find(id);
		if(it!=AssociationMap_.end())
		{
			return (*it).second();
		}
		return nullptr;
	}
protected:
	typedef std::map<IdentifierType,ProductCreator> AssociationsMap;
	AssociationsMap AssociationMap_;
};