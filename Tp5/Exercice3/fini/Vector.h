#ifndef VECTOR_H
#define VECTOR_H
#include "Point.h"
#include <GL/glut.h>
//#include "glut.h"

class Point;

class Vector
{
    private:
        double x;
        double y;
        double z;
    public:
        Vector();
        Vector(double x, double y, double z);
        virtual ~Vector();
        Vector(const Vector& V);
        double getX() const;
        double getY() const;
        double getZ() const;
        void setX(double px);
        void setY(double py);
        void setZ(double pz);
        double Norme();
        void Normalize();
        double Scalar(Vector Vector2);
        Vector Vectoriel(Vector Vector2);
        double Angle(Vector Vector2);
	void AfficherVector(Point p);
	Vector operator* (double a);
};

#endif // VECTOR_H
