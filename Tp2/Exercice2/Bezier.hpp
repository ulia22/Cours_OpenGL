#ifndef BEZIER_HPP
#define BEZIER_HPP
#include "Point.hpp"
#include <vector>


class Bezier
{
private:
	vector<Point> tabControlPoint;
	long nbControlPoint;
	long nbU;

	vector<Point> bezierCurve;
public:
	Bezier(void);
	Bezier(const vector<Point> tabControlPoint, const long nbControlPoint, const long nbU);
	Bezier(const &Bezier b);

	vector<Point> HermiteCubicCurve(vector<Point> myCurve, long nbU);

	vector<Point> getTabControlPoint(void);
	void setTabControlPoint(vector<Point> p);

	long getNbControlPoint(void);
	void setNbControlPoint(long n);

	long getNbU(void);
	void setNbU(long nbu);

	vector<Point> getBezierCurve(void);
	void setBezierCurve(vector<Point> curve);
};
#endif
