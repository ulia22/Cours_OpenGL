#include <iostream>
#include <vector>
#include "Casteljau.hpp"

using namespace std;

Point getCastlejauPoint(vector<vector<Point> > ptsControl, double s, double t){
	if(ptsControl.size() == 1 && ptsControl[0].size() == 1){
		return ptsControl[0][0];
	}
	vector<vector<Point> > res;
	Point Pij10;
	Point Pij01;
	Point Pij11;
	double x, y, z;
	unsigned int i,j;
	for(i = 0; i < ptsControl.size()-1; i++){
		res.push_back(vector<Point>());
		for(j = 0; j < ptsControl[i].size()-1; j++){
			x = (1-t)*ptsControl[i][j].getX() + t*ptsControl[i][j+1].getX();
			y = (1-t)*ptsControl[i][j].getY() + t*ptsControl[i][j+1].getY();
			z = (1-t)*ptsControl[i][j].getZ() + t*ptsControl[i][j+1].getZ();
			Pij01 = Point(x,y,z);

			x = (1-t)*ptsControl[i+1][j].getX() + t*ptsControl[i+1][j+1].getX();
			y = (1-t)*ptsControl[i+1][j].getY() + t*ptsControl[i+1][j+1].getY();
			z = (1-t)*ptsControl[i+1][j].getZ() + t*ptsControl[i+1][j+1].getZ();
			Pij10 = Point(x,y,z);

			x = (1-s)*Pij01.getX() + s*Pij10.getX();
			y = (1-s)*Pij01.getY() + s*Pij10.getY();
			z = (1-s)*Pij01.getZ() + s*Pij10.getZ();
			Pij11 = Point(x,y,z);
			//res[i].push_back(Point(Pij11));
		}
	}
	//return getCastlejauPoint(res, s, t);
	return Pij10;
}