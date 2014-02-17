#include "Bezier.hpp"
#include <cmath>
#include <iostream>

#include <GL/glut.h> 

long fact(long n);

	Bezier::Bezier(){
		this->setTabControlPoint(vector<Point>());
	}
	Bezier::Bezier(const vector<Point> tabControlPoint){
		this->setTabControlPoint(tabControlPoint);
	}
	Bezier::Bezier(const Bezier& p){
		//A faire plus tard.
	}

	/*
		Initialize la recurrence, et la lance.
	*/
	vector<Point> Bezier::bezierByCastlejau(long nbU){
		vector<Point> res = vector<Point>();

		res.push_back(this->getPointCastlejau(this->getTabControlPoint() , 0.0));

		for(long i = 1; i < nbU; i++){
			res.push_back(this->getPointCastlejau(this->getTabControlPoint(), (double)(1.0 / ((double)nbU - 1.0) * i)));
		}

		return res;
	}

	/*
		retourne un point de la courbe pour u entre 0 et 1.
	*/
	Point Bezier::getPointCastlejau(vector<Point> list, double u){
		if(list.size() == 1){
			return list[0];
		}

		vector<Point> nextList = vector<Point>();
		double x = 0.0, y = 0.0, z = 0.0;
		glBegin(GL_LINE_STRIP);
		for(unsigned int i = 0; i < list.size()-1; i++){
			x = (1.0 - u) * list[i].getX() + u * list[i+1].getX();
			y = (1.0 - u) * list[i].getY() + u * list[i+1].getY();
			z = (1.0 - u) * list[i].getZ() + u * list[i+1].getZ();
			nextList.push_back(Point(x,y,z));
			glVertex3f(x, y, z);
		}
		glEnd();
		return this->getPointCastlejau(nextList, u);
	}


	/*
		Retourne un vecteur de points (nbU points), qui representent la courbe de bezier, lesquels sont calculés avec les polynomes de bernstein.
	*/
	vector<Point> Bezier::bezierByBernstein(long nbU){
		vector<Point> res = vector<Point>();

		res.push_back(this->getPointByBernstein(0.0));

		for(long i = 1; i < nbU; i++){
			res.push_back(this->getPointByBernstein((double)(1.0 / ((double)nbU - 1.0) * i)));
		}

		return res;
	}

	Point Bezier::getPointByBernstein(double u){
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;

		//X
		for(long i = 0; i < (long)this->getTabControlPoint().size(); i++){
			x += this->getValBernsteinPoly(u, i, this->getTabControlPoint().size()-1) * this->getTabControlPoint()[i].getX();
		}

		//Y
		for(long i = 0; i < (long)this->getTabControlPoint().size(); i++){
			y += this->getValBernsteinPoly(u, i, this->getTabControlPoint().size()-1) * this->getTabControlPoint()[i].getY();
		}

		//Z
		for(long i = 0; i < (long)this->getTabControlPoint().size(); i++){
			z += this->getValBernsteinPoly(u, i, this->getTabControlPoint().size()-1) * this->getTabControlPoint()[i].getZ();
		}

		return Point(x, y, z);
	}

	/*
		Retourne la valeur d'un polynome de bernstein avec u en paramètre et i pour le choix du polynome et n pour le nombre total de polynomes qui sera considérés
	*/
	double Bezier::getValBernsteinPoly(double u, long i, long n){
		return (fact(n)/(fact(i)*fact(n-i)) * pow(u, (double)i) * pow(1-u, n-i));
	}

	long fact(long n)
	{
	  return (n == 1 || n == 0) ? 1 : fact(n - 1) * n;
	}

	vector<Point> Bezier::getTabControlPoint(void){return this->tabControlPoint;}
	void Bezier::setTabControlPoint(vector<Point> p){
		this->tabControlPoint = vector<Point>(p);
	}

	vector<Point> Bezier::getBezierCurve(void){return this->bezierCurve;}
	void Bezier::setBezierCurve(vector<Point> curve){}