#ifndef POINT_HPP
#define POINT_HPP
#include "Vector.hpp"
class Point
{
private:
	double x;
	double y;
	double z;
public:
	Point();
	Point(const double x, const double y, const double z);
	Point(const Point& p);

	Point ProjectOnLine(Point Point1Line, Point Point2Line);
	Point ProjectOnLine(Point p, Vector v);
	Point ProjectOnPlane(Point PointOnPlane, Vector NormalOfPlane);

	double getX(void);
	void setX(double x);

	double getY(void);
	void setY(double y);

	double getZ(void);
	void setZ(double Z);
};
#endif
