#include"ShapeFactory.h"

namespace graphics
{
	ShapeFactory::ShapeFactory()
	{

	}

	ShapeFactory::~ShapeFactory()
	{

	}

	bool ShapeFactory::RegisterShapeCallback(int ShapeId,CreateShapeCallback pFunc)
	{
		try
		{
			return CallbacksMap_.insert(ShapeMap::value_type(ShapeId,pFunc)).second;
		}
		catch (std::exception &e)
		{
			return false;
		}
		return true;
	}

	bool ShapeFactory::UnRegisterShapeCallback(int ShapeId)
	{
		try
		{
			return CallbacksMap_.erase(ShapeId)==1;
		}
		catch (std::exception &e)
		{
			return false;
		}
		return true;
	}

	Shape* ShapeFactory::CreateShape(int ShapeId)
	{
		ShapeMap::const_iterator it=CallbacksMap_.find(ShapeId);
		if(it==CallbacksMap_.end())
			return nullptr;
		return (*it).second();
	}
}
