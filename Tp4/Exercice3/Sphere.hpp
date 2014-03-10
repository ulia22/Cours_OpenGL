#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "Point.hpp"
#include <vector>

using namespace std;

class Sphere
{
private:
	double diametre;
	Point center;

public:
	Sphere(void);
	Sphere(Point _center, double _diametre);

	void display (long nbMeridian, long nbParallal);
	Point** computePoints(long nbMeridian, long nbParallal);

	double getDiametre(void);
	void setDiametre(double _diam);

	Point getCenter(void);
	void setCenter(Point _center);
};
	
#endif