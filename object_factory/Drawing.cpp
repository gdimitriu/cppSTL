#include "Drawing.h"
#include <iostream>
#include "Factory.h"

namespace graphics
{
	typedef singleton_static<Factory<Shape,unsigned int>> SingletonFactory;
	Drawing::Drawing()
	{
		SingletonShapeFactory::Instance().RegisterShapeCallback(RECTANGLE,CreateRectangle);
		SingletonShapeFactory::Instance().RegisterShapeCallback(CIRCLE,CreateCircle);
		SingletonFactory::Instance().RegisterCreator(RECTANGLE,CreateRectangle);
		SingletonFactory::Instance().RegisterCreator(CIRCLE,CreateCircle);
	}

	Drawing::~Drawing()
	{
		for(std::vector<Shape *>::reverse_iterator i=vElements_.rbegin();i!=vElements_.rend();++i)
			delete (*i);
		vElements_.clear();
	}

	void Drawing::Draw(CClientDC *pDC)
	{
		for(std::vector<Shape *>::iterator it=vElements_.begin();it!=vElements_.end();++it)
			(*it)->Draw(pDC);
	}

	void Drawing::AddShape(Shape* obj)
	{
		vElements_.push_back(obj);
	}

	void Drawing::Clear()
	{
		for(std::vector<Shape *>::reverse_iterator i=vElements_.rbegin();i!=vElements_.rend();++i)
			delete (*i);
		vElements_.clear();
	}

	void Drawing::Save(std::ofstream& oFile)
	{
		unsigned int DrawingType;
		for(std::vector<Shape *>::iterator it=vElements_.begin();it!=vElements_.end();++it)
		{
			DrawingType=(*it)->GetDrawingType();
			oFile.write((char*)(&DrawingType),sizeof(unsigned int));
			(*it)->Save(oFile);
		}
	}
	void Drawing::Load(std::ifstream& iFile)
	{
/*		unsigned int DrawingType;
		while(!iFile.eof())
		{
			iFile.read((char*)(&DrawingType),sizeof(unsigned int));
			if(iFile.eof())
				return;
			Shape *pShape;
			pShape=nullptr;
			switch(DrawingType)
			{
			case RECTANGLE:
				{
					pShape=new Rectangle();
					break;
				}
			case CIRCLE:
				{
					pShape=new Circle();
					break;
				}
			}
			if(pShape!=nullptr)
			{
				pShape->Load(iFile);
				vElements_.push_back(pShape);
			}
		}
*/
		unsigned int DrawingType;
		while(!iFile.eof())
		{
			iFile.read((char*)(&DrawingType),sizeof(unsigned int));
			if(iFile.eof())
				return;
			Shape *pShape;
			pShape=nullptr;
//			pShape=SingletonShapeFactory::Instance().CreateShape(DrawingType);

			pShape=SingletonFactory::Instance().CreateObject(DrawingType);
			if(pShape!=nullptr)
			{
				pShape->Load(iFile);
				vElements_.push_back(pShape);
			}
		}
	}
}