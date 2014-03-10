#include <iostream>
#include <vector>
#include "Sphere.hpp"
#include <cmath>
#include <GL/glut.h> 

using namespace std;

#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

Sphere::Sphere(void)
{
	this->setDiametre(1.0);
	this->setCenter(Point(0.0,0.0,0.0));
}
Sphere::Sphere(Point _center, double _diametre){
	this->setDiametre(diametre);
	this->setCenter(center);
}

void Sphere::display (long nbMeridian, long nbParallal){
	Point **sphere = this->computePoints(nbMeridian, nbParallal);

	for(int i = 0; i <nbParallal+1; i++){
		glBegin(GL_LINE_STRIP);
			for(int j = 0; j < nbMeridian+1; j++){
				glVertex3f(sphere[i][j].getX(), sphere[i][j].getY(), sphere[i][j].getZ());
			}
		glEnd();
	}

	for(int i = nbParallal; i < nbParallal+nbMeridian+1; i++){
		glBegin(GL_LINE_STRIP);
			for(int j = 0; j < nbParallal+1; j++){
				glVertex3f(sphere[i][j].getX(), sphere[i][j].getY(), sphere[i][j].getZ());
			}
		glEnd();
	}
}

Point** Sphere::computePoints(long nbMeridian, long nbParallal){
	Point **res = new Point*[(nbMeridian+1) * (nbParallal+1) + 2];

	double teta;
	double phi;


	for(int i = 0; i < nbParallal+1; ++i){
		phi = (M_PI / (double)nbParallal)*(double)i;
		res[i] = new Point[nbMeridian+1];
		for(int j = 0; j < nbMeridian+1; ++j){
			teta = (2.*M_PI/(double)nbMeridian)*(double)j;
			res[i][j] = Point( (this->getDiametre() / 2.)*sin(phi)*cos(teta),(this->getDiametre() / 2.)*sin(phi)*sin(teta), (this->getDiametre() / 2.)*cos(phi));
		}
	}

	for(int j = 0; j < nbMeridian+1; ++j){
		teta = (2.*M_PI/(double)nbMeridian)*(double)j;
		for(int i = 0; i < nbParallal+1; ++i){
			phi = (M_PI / (double)nbParallal)*(double)i;
			res[nbParallal + j] = new Point[nbParallal+1];
			res[i][j] = Point( (this->getDiametre() / 2.)*sin(phi)*cos(teta),(this->getDiametre() / 2.)*sin(phi)*sin(teta), (this->getDiametre() / 2.)*cos(phi));
		}
	}

	return res;
}


double Sphere::getDiametre(void){return diametre;}
void Sphere::setDiametre(double _diam){diametre = _diam;}

Point Sphere::getCenter(void){return center;}
void Sphere::setCenter(Point _center){center = _center;}