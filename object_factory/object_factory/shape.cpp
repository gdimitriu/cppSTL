#include "shape.h"

namespace graphics
{
	//save the x and y from shape base class
	void Shape::Save(std::ofstream& oFile)
	{
		oFile.write((char*)(&x_),sizeof(unsigned int));
		oFile.write((char*)(&y_),sizeof(unsigned int));
	}

	//load the x and y from shape base class
	void Shape::Load(std::ifstream& iFile)
	{
		iFile.read((char*)(&x_),sizeof(unsigned int));
		iFile.read((char*)(&y_),sizeof(unsigned int));
	}
	unsigned int Shape::GetDrawingType(void)
	{
		return SHAPE;
	}
}