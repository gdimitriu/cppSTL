// adt_objects.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ostream>

class Point3d_full
{
public:
	Point3d_full(float x=0.0,float y=0.0,float z=0.0) :_x(x),_y(y),_z(z) {}
	float x(void) const { return _x;}
	float y(void) const { return _y;}
	float z(void) const { return _z;}
	void x(float xval) {_x=xval;}
	void y(float yval) {_y=yval;}
	void z(float zval) {_z=zval;}
private:
	float _x;
	float _y;
	float _z;
};

inline std::ostream& operator<<(std::ostream &os,const Point3d_full &pt)
{
	os<<"("<<pt.x()<<", "<<pt.y()<<", "<<pt.z()<<" )";
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

