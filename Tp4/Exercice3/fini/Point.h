#ifndef POINT_H
#define POINT_H
#include <GL/glut.h>
//#include "glut.h"
#include "Vector.h"

class Vector;

class Point
{
    private:
        double x;
        double y;
        double z;
    public:
        Point();
        Point(double px, double py, double pz);
        Point(const Point& P);
        virtual ~Point();
        double getX () const;
        double getY() const ;
        double getZ () const;
        void setX(double px);
        void setY(double py);
        void setZ(double pz);
        Point ProjectOnLine(Point Point1Line, Point Point2Line);
        Point ProjectOnLine(Point Point1, Vector vecteur);
        Point ProjectOnPlan(Point PointOnPlane, Vector NormalOfPlane);
	void AfficherPoint();
	Point operator+ (Point p1);
	Point operator+ (Vector v1);
	Point operator* (double a);
    protected:

};

#endif // POINT_H
