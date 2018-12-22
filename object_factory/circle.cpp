#include"circle.h"
namespace graphics
{
	void Circle::Draw(CClientDC* pDC)
	{
		pDC->Ellipse(x_-iRadius_,y_-iRadius_,x_+iRadius_,y_+iRadius_);
	}

	void Circle::Save(std::ofstream& oFile)
	{
		Shape::Save(oFile);
		oFile.write((char*)(&iRadius_),sizeof(unsigned int));
	}

	void Circle::Load(std::ifstream& iFile)
	{
		Shape::Load(iFile);
		iFile.read((char*)(&iRadius_),sizeof(unsigned int));
	}
	unsigned int Circle::GetDrawingType(void)
	{
		return CIRCLE;
	}

	Shape* CreateCircle()
	{
		return new Circle;
	}

}