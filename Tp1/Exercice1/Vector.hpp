#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector
{
private : 
	double x;
	double y;
	double z;
public : 
	Vector();
	Vector(double x, double y, double z);
	Vector(const Vector&);

	double norme();
	void normalize();
	double scalar(Vector v);
	Vector vectoriel(Vector v);
	double angle(Vector v);

	/*
		Getters and setters
	*/
	double getX(void);
	double getY(void);
	double getZ(void);

	void setX(double x);
	void setY(double y);
	void setZ(double z);
};
#endif
