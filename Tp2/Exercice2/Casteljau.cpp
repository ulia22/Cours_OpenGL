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

int main(){

	Point P00(0,0,0), P01(0,1,0), P02(0,2,0);
	Point P10(1,0,0), P11(1,1,1), P12(1,2,1);
	Point P20(2,0,0), P21(2,1,1), P22(2,2,1);
	Point P30(3,0,0), P31(3,1,0), P32(3,2,0);
	vector<Point> v00, v10, v20, v30;
	v00.push_back(P00);
	v00.push_back(P01);
	v00.push_back(P02);

	v10.push_back(P10);
	v10.push_back(P11);
	v10.push_back(P12);

	v20.push_back(P20);
	v20.push_back(P21);
	v20.push_back(P22);

	v30.push_back(P30);
	v30.push_back(P31);
	v30.push_back(P32);

	vector<vector<Point> > ptsControl;
	ptsControl.push_back(v00);
	ptsControl.push_back(v10);
	ptsControl.push_back(v20);
	ptsControl.push_back(v30);

	double s = 0.25, t = 0.50;

	cout << " X = " << getCastlejauPoint(ptsControl, s, t).getX() << " Y = " << getCastlejauPoint(ptsControl, s, t).getY()<< " Z = " << getCastlejauPoint(ptsControl, s, t).getZ() << endl;

	return 0;
}