//find the average of a range of points
#include<iostream>
#include<list>
#include<algorithm>
#include<functional>
#include<numeric>
using std::list;

struct Point
{
	Point(double initX,double initY): x(initX),y(initY){}
	double x,y;
};
class PointAverage: public std::binary_function<Point,Point,Point>
{
public:
	PointAverage():xSum(0),ySum(0),numPoints(0){}
	const Point operator()(const Point& avgSoFar,const Point& p)
	{
		++numPoints;
		xSum+=p.x;
		ySum+=p.y;
		return Point(xSum/numPoints,ySum/numPoints);
	}
private:
	size_t numPoints;
	double xSum;
	double ySum;
};

int main()
{
	list<Point> lp;

	Point avg=std::accumulate(lp.begin(),lp.end(),Point(0,0),PointAverage());
}