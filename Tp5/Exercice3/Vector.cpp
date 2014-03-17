#include "Vector.hpp"
#include <cmath>

Vector::Vector() : x(0.0), y(0.0), z(0.0)
{}

Vector::Vector(const double x, const double y, const double z) : x(x), y(y), z(z)
{}

Vector::Vector(const Vector& v) : x(v.x), y(v.y), z(v.z)
{}

double Vector::norme(){
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vector::normalize(){
	double norme = this->norme();
	this->x /= norme;
	this->y /= norme;
	this->z /= norme;
}

double Vector::scalar(Vector v){
	return (this->x * v.getX() + this->y * v.getY() + this->z * v.getZ());
}

Vector Vector::vectoriel(Vector v){
	return Vector((this->y * v.getZ() - this->z * v.getY()),
			(this->z * v.getX() - this->x * v.getZ()),
			(this->x * v.getY() - this->y * v.getX()));
}
double Vector::angle(Vector v){
	return acos(this->scalar(v)/(this->norme()*v.norme()));
}

/*
	Getters and setters
*/
double Vector::getX(){
	return this->x;
}
double Vector::getY(){
	return this->y;
}
double Vector::getZ(){
	return this->z;
}

void Vector::setX(double x){
	this->x = x;
}
void Vector::setY(double y){
	this->y = y;
}
void Vector::setZ(double z){
	this->z = z;
}
