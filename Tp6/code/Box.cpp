#include <iostream>
#include <vector>
#include "Box.hpp"
#include <cmath>
#include "Vector.hpp"
#include <GL/glut.h> 

using namespace std;

	Box::Box(void){
		this->setA(Point(1.0, 1.0, 0.0));
		this->setB(Point(-1.0, -1.0, 0.0));
		this->setCubesSize((double)0.1);
		maxX = (long) sqrt(pow((double)this->getB().getX() - (double)this->getA().getX(), 2.) + pow((double)this->getB().getY() - (double)this->getA().getY(), 2.) + pow((double)this->getB().getZ() - (double)this->getA().getZ(), 2.)) / this->getCubesSize();
		maxY = maxX;
		maxZ = maxX;
		cubes = vector<vector <vector <bool> > >();
	}
	Box::Box(Point _A, Point _B){
		this->setA(_A);
		this->setB(_B);
		this->setCubesSize(0.1);
		//cout << sqrt(pow((double)this->getB().getX() - (double)this->getA().getX(), 2.) + pow((double)this->getB().getY() - (double)this->getA().getY(), 2.) + pow((double)this->getB().getZ() - (double)this->getA().getZ(), 2.)) / this->getCubesSize()<<endl;
		maxX = (long) sqrt(pow((double)this->getB().getX() - (double)this->getA().getX(), 2.) + pow((double)this->getB().getY() - (double)this->getA().getY(), 2.) + pow((double)this->getB().getZ() - (double)this->getA().getZ(), 2.)) / this->getCubesSize();
		maxY = maxX;
		maxZ = maxX;
		cubes = vector<vector <vector <bool> > >();
	}

	Point Box::getA(void){return A;}
	void Box::setA(Point _A){A = _A;}

	Point Box::getB(void){return B;}
	void Box::setB(Point _B){B = _B;};

	long Box::getMaxX(){return maxX;}
	long Box::getMaxY(){return maxY;}
	long Box::getMaxZ(){return maxZ;}

	double Box::getCubesSize(void){return cubesSize;}
	void Box::setCubesSize(double _size){cubesSize = _size;}

	vector< vector< vector<bool> > >* Box::getCubes(void){return &cubes;}

	vector<Point> Box::getCube(unsigned x, unsigned y, unsigned z){
		//X
		while(!(this->getCubes()->size() > x)){
			this->getCubes()->push_back(vector<vector<bool> >());
		}

		//Y
		while(!(this->getCubes()->at(x).size() > y)){
			this->getCubes()->at(x).push_back(vector<bool>());
		}

		//Z
		while(!(this->getCubes()->at(x).at(y).size() > z)){
			this->getCubes()->at(x).at(y).push_back(false);
		}
		vector<Point> res = vector<Point>();
		Vector v = Vector(B.getX()-A.getX(), B.getY()-A.getY(), B.getZ()-A.getZ());

		res.push_back(Point(v.getX() + this->getCubesSize() * (double)x, 	  v.getY() + this->getCubesSize() * (double)y, 		v.getZ() + this->getCubesSize() * (double)z));
		res.push_back(Point(v.getX() + this->getCubesSize() * (double)(x+1),  v.getY() + this->getCubesSize() * (double)y, 		v.getZ() + this->getCubesSize() * (double)z));
		res.push_back(Point(v.getX() + this->getCubesSize() * (double)x,      v.getY() + this->getCubesSize() * (double)(y+1), 	v.getZ() + this->getCubesSize() * (double)z));
		res.push_back(Point(v.getX() + this->getCubesSize() * (double)(x+1),  v.getY() + this->getCubesSize() * (double)(y+1), 	v.getZ() + this->getCubesSize() * (double)z));

		res.push_back(Point(v.getX() + this->getCubesSize() * (double)x, 	 v.getY() + this->getCubesSize() * (double)y,	 	v.getZ() +  this->getCubesSize() * (double)(z+1) ));
		res.push_back(Point(v.getX() + this->getCubesSize() * (double)(x+1), v.getY() + this->getCubesSize() * (double)y,	 	v.getZ() +  this->getCubesSize() * (double)(z+1) ));
		res.push_back(Point(v.getX() + this->getCubesSize() * (double)x, 	 v.getY() + this->getCubesSize() * (double)(y+1),	v.getZ() +  this->getCubesSize() * (double)(z+1) ));
		res.push_back(Point(v.getX() + this->getCubesSize() * (double)(x+1), v.getY() + this->getCubesSize() * (double)(y+1),	v.getZ() +  this->getCubesSize() * (double)(z+1) ));

		return res;
	}
	void Box::setCubeVal(unsigned x, unsigned y, unsigned z, bool val){
		this->getCubes()->at(x).at(y).at(z) = val;
	}
	bool Box::getCubeVal(unsigned x, unsigned y, unsigned z){
		return this->getCubes()->at(x).at(y).at(z);
	}