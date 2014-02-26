#ifndef HERMITE_HPP
#define HERMITE_HPP
#include "Point.hpp"

class Hermite
{
private:
	Point 	P0;
	Vector 	T0;
	Point 	P1;
	Vector 	T1;
public:
	Hermite();
	Hermite(const Point P0, const Vector T0, const Point P1, const Vector T1);
	Hermite(const Hermite& p);

	Point* HermiteCubicCurve(Point* myCurve, long nbU);

	Point getP0(void);
	void setP0(Point p);

	Vector getT0(void);
	void setT0(Vector v);

	Point getP1(void);
	void setP1(Point p);

	Vector getT1(void);
	void setT1(Vector v);
};
#endif
