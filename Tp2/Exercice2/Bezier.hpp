#ifndef BEZIER_HPP
#define BEZIER_HPP
#include "Point.hpp"
#include <vector>

using namespace std;

class Bezier
{
private:
	vector<Point> tabControlPoint;

	vector<Point> bezierCurve;
public:
	Bezier(void);
	Bezier(const vector<Point> tabControlPoint);
	Bezier(const Bezier& b);

	vector<Point> bezierByBernstein(long nbU);
	Point getPointByBernstein(double u);
	double getValBernsteinPoly(double u, long i, long n);
	vector<Point> bezierByCastlejau(long nbU);
	Point getPointCastlejau(vector<Point> list, double u);

	vector<Point> getTabControlPoint(void);
	void setTabControlPoint(vector<Point> p);

	vector<Point> getBezierCurve(void);
	void setBezierCurve(vector<Point> curve);
};
#endif
