#pragma once
#include"shape.h"
namespace graphics
{
	class Circle : public Shape
	{
	public:
		Circle():Shape(0,0),iRadius_(0){};
		Circle(unsigned int x,unsigned int y,unsigned int radius) : Shape(x,y),iRadius_(radius){};
		~Circle(){};
		void Draw(CClientDC* pDC);
		void Save(std::ofstream& oFile);
		void Load(std::ifstream& iFile);
		unsigned int GetDrawingType(void);
	private:
		unsigned int iRadius_;
	};

	Shape* CreateCircle();
}