#include "Hermite.hpp"
#include <cmath>
#include <iostream>
Hermite::Hermite()
{}
Hermite::Hermite(const Point P0, const Vector T0, const Point P1, const Vector T1){
	this->setP0(P0);
	this->setT0(T0);
	this->setP1(P1);
	this->setT1(T1);
}
Hermite::Hermite(const Hermite& p){
	this->P0 = p.P0;
	this->T0 = p.T0;
	this->P1 = p.P1;
	this->T1 = p.T1;
}

Point* Hermite::HermiteCubicCurve(Point* myCurve, long nbU2){
	double i = 0.;
	int j = 0;
	long nbU = nbU2 - 1;
	double F0, F1, F2, F3, Xi, Yi, Zi;
	for(j = 0; j < nbU; j++){
		i = ((double)j/nbU);
		F0 =  2 * pow(i, 3.) - 3 * pow(i, 2.) + 1;
		F1 = -2 * pow(i, 3.) + 3 * pow(i, 2.);
		F2 = pow(i, 3.) - 2 * pow(i, 2.) + i;
		F3 = pow(i, 3.) - pow(i, 2.);

		Xi = F0*this->getP0().getX() + F1*this->getP1().getX() + F2*this->getT0().getX() + F3*this->getT1().getX();
		Yi = F0*this->getP0().getY() + F1*this->getP1().getY() + F2*this->getT0().getY() + F3*this->getT1().getY();
		Zi = F0*this->getP0().getZ() + F1*this->getP1().getZ() + F2*this->getT0().getZ() + F3*this->getT1().getZ();
		myCurve[j].setX(Xi);
		myCurve[j].setY(Yi);
		myCurve[j].setZ(Zi);
	}
	myCurve[nbU].setX(this->getP1().getX());
	myCurve[nbU].setY(this->getP1().getY());
	myCurve[nbU].setZ(this->getP1().getZ());
	return myCurve;
}

Point Hermite::getP0(void){return this->P0;}
void Hermite::setP0(Point p){this->P0 = p;}

Vector Hermite::getT0(void){return this->T0;}
void Hermite::setT0(Vector v){this->T0 = v;}

Point Hermite::getP1(void){return this->P1;}
void Hermite::setP1(Point p){this->P1 = p;}

Vector Hermite::getT1(void){return this->T1;}
void Hermite::setT1(Vector v){this->T1 = v;}