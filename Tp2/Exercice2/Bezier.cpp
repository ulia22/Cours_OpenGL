#include "Bezier.hpp"
#include <cmath>
#include <iostream>

	Bezier::Bezier(){
		this->setNbU(0);
		this->setNbControlPoint(0);
	}
	Bezier::Bezier(const vector<Point> tabControlPoint, const long nbControlPoint, const long nbU){
		this->setTabControlPoint(tabControlPoint);
		this->setNbControlPoint(nbControlPoint);
		this->setNbU(nbU);
	}
	Bezier::Bezier(const &Bezier p){
		
	}

	vector<Point> Bezier::HermiteCubicCurve(vector<Point> myCurve, long nbU){

	}

	vector<Point> Bezier::getTabControlPoint(void){return this->tabControlPoint;}
	void Bezier::setTabControlPoint(vector<Point> p, long nbc){
		for(long i = 0; i < nbc; i++){
			this->tabControlPoint[i].(p[i]);
		}
	}

	long Bezier::getNbControlPoint(void){return this->nbControlPoint;}
	void Bezier::setNbControlPoint(long n){this->nbControlPoint = n;}

	long Bezier::getNbU(void){return this->nbU;}
	void Bezier::setNbU(long nbu){this->nbU = nbu;}

	vector<Point> Bezier::getBezierCurve(void){return this->bezierCurve;}
	void Bezier::setBezierCurve(vector<Point> curve){}