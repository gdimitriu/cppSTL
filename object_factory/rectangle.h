#pragma once
#include"shape.h"
namespace graphics
{
	class Rectangle : public Shape
	{
	public:
		Rectangle():Shape(0,0),width_(0),heigth_(0){};
		~Rectangle(){};
		Rectangle(unsigned int x,unsigned int y,unsigned int width,unsigned int heigth) : Shape(x,y),width_(width),heigth_(heigth){};
		void Save(std::ofstream& oFile);
		void Load(std::ifstream& iFile);
		unsigned int GetDrawingType(void);
		void Draw(CClientDC* pDC);
	private:
		unsigned int width_;
		unsigned int heigth_;
	};
	
	Shape* CreateRectangle();
}