#include "rectangle.h"
namespace graphics
{
	void Rectangle::Draw(CClientDC *pDC)
	{
		pDC->Rectangle(x_-width_/2,y_-heigth_/2,x_+width_/2,y_+heigth_/2);
	}

	//save the rectangle variables
	void Rectangle::Save(std::ofstream& oFile)
	{
		//save the base class
		Shape::Save(oFile);
		//save the rectangle specifics
		oFile.write((char*)(&width_),sizeof(unsigned int));
		oFile.write((char*)(&heigth_),sizeof(unsigned int));
	}
	//load the rectangle variables
	void Rectangle::Load(std::ifstream& iFile)
	{
		//load the base class
		Shape::Load(iFile);
		//load the rectagle specifics
		iFile.read((char*)(&width_),sizeof(unsigned int));
		iFile.read((char*)(&heigth_),sizeof(unsigned int));
	}
	unsigned int Rectangle::GetDrawingType(void)
	{
		return RECTANGLE;
	}

	Shape* CreateRectangle()
	{
		return new Rectangle;
	}
}