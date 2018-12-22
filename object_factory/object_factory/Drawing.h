#pragma once
#include "shape.h"
#include <vector>
#include "circle.h"
#include "rectangle.h"
#include "ShapeFactory.h"

namespace graphics
{
	class Drawing
	{
	public:
		Drawing();
		~Drawing();
		void Draw(CClientDC *pDC);
		void AddShape(Shape* elem);
		void Save(std::ofstream& oFile);
		void Load(std::ifstream& iFile);
		void Clear();
	private:
		std::vector<Shape *> vElements_;
	};
}