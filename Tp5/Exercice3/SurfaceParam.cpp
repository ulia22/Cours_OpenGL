#include "SurfaceParam.hpp"
#include <GL/glut.h> 
#include <iostream>

SurfaceParam::SurfaceParam(){
	this->setNbParall(10);
	this->setParall(new Point*[10+1]);
}
SurfaceParam::SurfaceParam(vector<Point> _bezier1, vector<Point> _bezier2, int _nbParall){
	this->setBezier1(_bezier1);
	this->setBezier2(_bezier2);
	this->setParall(new Point* [_nbParall+1]);
	this->setNbParall(_nbParall);
}
SurfaceParam::SurfaceParam(const SurfaceParam& s){
	bezier1 = s.bezier1;
	bezier2 = s.bezier2;
	parall = s.parall;
	nbParall = s.nbParall;
}

void SurfaceParam::computeSurface(void){
	//On definie le vecteur de la droite qui passera entre les deux bezier de depart comme un vecteur.
	//Il suffira de diviser ce vecteur, et de translater la pts de départ pour avoir un point sur la courbe.
	//On appellera cela un meridien
	Vector meridian;
	Point ptsBegin, ptsEnd;

	//Pour chaque parallele à créer
	for(int i = 0; i < this->getNbParall()+1; ++i){
		this->getParall()[i] = new Point[this->getBezier1().size()];
		//On calcule les points sur les méridiens
		for(unsigned int j = 0; j < this->getBezier1().size(); ++j){
			ptsBegin = this->getBezier1().at(j);
			ptsEnd = this->getBezier2().at(j);
			meridian = Vector(ptsEnd.getX() - ptsBegin.getX(), ptsEnd.getY() - ptsBegin.getY(), ptsEnd.getZ() - ptsBegin.getZ());

			meridian.setX((double)meridian.getX()* (1./this->getNbParall()) * i);
			meridian.setY((double)meridian.getY()* (1./this->getNbParall()) * i);
			meridian.setZ((double)meridian.getZ()* (1./this->getNbParall()) * i);

			this->getParall()[i][j] = Point(ptsBegin.getX() + meridian.getX(), ptsBegin.getY() + meridian.getY(), ptsBegin.getZ() + meridian.getZ());
			cout <<"i : " << i << " j : "<< j << " " <<getParall()[i][j].getX() <<endl;
		}
	}
}

void SurfaceParam::displaySurface(void){

	//Les deux beziers.
	glBegin(GL_LINE_STRIP);
		for(unsigned int i = 0; i < this->getBezier1().size(); ++i){
			glVertex3f(this->getBezier1().at(i).getX(), this->getBezier1().at(i).getY(), this->getBezier1().at(i).getZ());
		}
	glEnd();

	glBegin(GL_LINE_STRIP);
		for(unsigned int i = 0; i < this->getBezier2().size(); ++i){
			glVertex3f(this->getBezier2().at(i).getX(), this->getBezier2().at(i).getY(), this->getBezier2().at(i).getZ());
		}
	glEnd();

	//Les meridiens
	for(unsigned int i = 0; i < this->getBezier1().size(); ++i){
		glBegin(GL_LINES);
			glVertex3f(this->getBezier1().at(i).getX(), this->getBezier1().at(i).getY(), this->getBezier1().at(i).getZ());
			glVertex3f(this->getBezier2().at(i).getX(), this->getBezier2().at(i).getY(), this->getBezier2().at(i).getZ());
		glEnd();
	}

	//Les paralleles
	//cout << this->getParall().size() <<endl;
	//cout << this->getParall().at(0).size() <<endl;
	for(int i = 0; i < this->getNbParall()+1; ++i){
		glBegin(GL_LINE_STRIP);
		for(unsigned int j = 0; j < this->getBezier1().size(); j++){
			glVertex3f(this->getParall()[i][j].getX(), this->getParall()[i][j].getY(), this->getParall()[i][j].getZ());
		}
		glEnd();
	}

	//Les triangles !

	for(int i = 0; i < this->getNbParall(); ++i){

		for(unsigned int j = 0; j < this->getBezier1().size()-1; j++){
			glBegin(GL_LINE_STRIP);
				glVertex3f(this->getParall()[i][j].getX(), this->getParall()[i][j].getY(), this->getParall()[i][j].getZ());
				glVertex3f(this->getParall()[i+1][j+1].getX(), this->getParall()[i+1][j+1].getY(), this->getParall()[i+1][j+1].getZ());
			glEnd();
		}
	}
}


/*
	Getters and setters
*/
vector<Point> SurfaceParam::getBezier1(void){return bezier1;}
vector<Point> SurfaceParam::getBezier2(void){return bezier2;};
Point** SurfaceParam::getParall(void){return parall;}
int SurfaceParam::getNbParall(void){return nbParall;}

void SurfaceParam::setBezier1(vector<Point> _b1){bezier1 = _b1;}
void SurfaceParam::setBezier2(vector<Point> _b2){bezier2 = _b2;}
void SurfaceParam::setParall(Point** _par){parall = _par;}
void SurfaceParam::setNbParall(int _nb){nbParall = _nb;}