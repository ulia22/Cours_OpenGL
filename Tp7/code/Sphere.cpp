#include <iostream>
#include <vector>
#include "Sphere.hpp"
#include "Box.hpp"
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

void Sphere::displayVolCube(){
	Point A = Point(this->getCenter().getX() + ((double)this->getDiametre()/2.), this->getCenter().getY() + ((double)this->getDiametre()/2.), this->getCenter().getZ() + ((double)this->getDiametre()/2.));
	Point B = Point(this->getCenter().getX() - ((double)this->getDiametre()/2.), this->getCenter().getY() + ((double)this->getDiametre()/2.), this->getCenter().getZ() + ((double)this->getDiametre()/2.));
	//cout << A.getX() <<" "<< A.getY() <<" "<< A.getZ() <<" "<< B.getX() <<" "<< B.getY() <<" "<< B.getZ() <<endl;
	Box box = Box(A, B);
	//cout <<
	vector<Point> currCube;
	double dist;
cout << "test1 "<<box.getMaxX()<< box.getMaxY()<< box.getMaxZ()<<endl;
	for(long x = 0; x < box.getMaxX(); x++){
		//cout << "test2"<<endl;
		for(long y = 0; y < box.getMaxY(); y++){
			//cout << "test3"<<endl;
			for(long z = 0; z < box.getMaxZ(); z++){
				//cout << "test4"<<endl;
				currCube = vector<Point>(box.getCube(x, y, z));
				//cout <<  currCube.size() <<endl;
				for(unsigned i = 0; i < currCube.size(); i++){
					//cout << "test5"<<endl;
					//cout << currCube[i].getX()<<" " << currCube[i].getY()<<" "<< currCube[i].getZ() << endl;
					dist = sqrt(pow(this->getCenter().getX() - currCube[i].getX(), 2.) +  pow(this->getCenter().getY() - currCube[i].getY(), 2.) + pow(this->getCenter().getZ() - currCube[i].getZ(), 2.));
					/*cout << dist << endl;
					cout << this->getDiametre()/2. <<endl;*/
					if(dist <= this->getDiametre()/2.){
						//cout << "test6"<<endl;
						box.setCubeVal(x, y, z, true);
					}
				}
				//On affiche le cube si il est a true
				if(/*box.getCubeVal(x, y, z)*/true){
					//cout << "test7"<<endl;
					glBegin(GL_LINE_STRIP);
					for(unsigned i = 0; i < currCube.size(); i++){
						//cout << currCube[i].getX()<<" " << currCube[i].getY()<<" "<< currCube[i].getZ() << endl;
						glVertex3f(currCube[i].getX(), currCube[i].getY(), currCube[i].getZ());
						
					}
					glEnd();
					//glFlush();
				}
			}
		}
	}
	cout << "Fin "<<endl;
	glFlush();
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
	Point **res = new Point* [(nbMeridian+1) + (nbParallal+1) + 2];

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

		res[nbParallal + j] = new Point[nbParallal+1];
		for(int i = 0; i < nbParallal+1; ++i){
			phi = (M_PI / (double)nbParallal)*(double)i;

			res[nbParallal + j][i] = Point( (this->getDiametre() / 2.)*sin(phi)*cos(teta),(this->getDiametre() / 2.)*sin(phi)*sin(teta), (this->getDiametre() / 2.)*cos(phi));
			
			cout << "res ["<<i<<', '<< j <<"] = ("<< res[nbParallal + j][i].getX() <<", "<< res[nbParallal + j][i].getY() << ", "<< res[nbParallal + j][i].getZ() <<" )."<<endl;
		}
	}

	return res;
}


double Sphere::getDiametre(void){return diametre;}
void Sphere::setDiametre(double _diam){diametre = _diam;}

Point Sphere::getCenter(void){return center;}
void Sphere::setCenter(Point _center){center = _center;}