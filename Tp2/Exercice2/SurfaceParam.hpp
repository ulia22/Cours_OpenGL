#ifndef SURFACEPARAM_HPP
#define SURFACEPARAM_HPP
#include <vector>
#include "Point.hpp"

using namespace std;

class SurfaceParam
{
private : 
	vector<Point> bezier1;
	vector<Point> bezier2;

	vector<vector<Point> > parall;

	int nbParall;

public : 
	SurfaceParam();
	SurfaceParam(vector<Point> _bezier1, vector<Point> _bezier2, int _nbParall);
	SurfaceParam(const SurfaceParam& s);


	/*
		Getters and setters
	*/
	vector<Point> getBezier1(void);
	vector<Point> getBezier2(void);
	vector<vector<Point> > getParall(void);
	int getNbParall(void);

	void setBezier1(vector<Point> _b1);
	void setBezier2(vector<Point> _b2);
	void setParall(vector<vector<Point> > _par);
	void setNbParall(int _nb);
};
#endif
