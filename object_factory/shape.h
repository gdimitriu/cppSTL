#pragma once
#include <fstream>
#include <afxwin.h>
#include "constants.h"
namespace graphics
{
	class Shape
	{
	public:
		Shape():x_(0),y_(0){};
		Shape(unsigned int x,unsigned int y) : x_(x),y_(y){};
		virtual ~Shape(){};
		virtual void Draw(CClientDC* pDC)=0;
	//	virtual void Rotate(double angle)=0;
	//	virtual void Zoom(double ratio)=0;
		virtual void Save(std::ofstream& oFile);
		virtual void Load(std::ifstream& iFile);
		virtual unsigned int GetDrawingType(void);
		void SetX(unsigned int x) {x_=x;}
		void SetY(unsigned int y) {y_=y;}
		unsigned int GetX(void) { return x_;}
		unsigned int GetY(void) { return y_;}
	protected:
		unsigned int x_;
		unsigned int y_;
	};
}