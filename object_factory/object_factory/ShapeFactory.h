#pragma once
#include<map>
#include "shape.h"
#include "singletons.h"


namespace graphics
{
	class ShapeFactory
	{
	public:
		ShapeFactory();
		~ShapeFactory();
		typedef Shape* (*CreateShapeCallback)();
		//this should return false if it could not register and true if it is successful
		bool RegisterShapeCallback(int ShapeId,CreateShapeCallback pFunc);
		//this should return false if it could not unregister and true if it is successful
		bool UnRegisterShapeCallback(int ShapeId);
		Shape* CreateShape(int ShapeId);
	protected:
		typedef std::map<int,CreateShapeCallback> ShapeMap;
		ShapeMap CallbacksMap_;
	};
	typedef singleton_static<ShapeFactory> SingletonShapeFactory;
}