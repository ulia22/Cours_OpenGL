#ifndef BOX_HPP
#define BOX_HPP
#include "Point.hpp"
#include <vector>

using namespace std;

class Box
{
private:
	Point A;
	Point B;

	long maxX;
	long maxY;
	long maxZ;

	double cubesSize;
	vector<vector <vector <bool> > > cubes;

public:
	Box(void);
	Box(Point _A, Point _B);

	Point getA(void);
	void setA(Point _A);

	Point getB(void);
	void setB(Point _B);

	double getCubesSize(void);
	void setCubesSize(double _size);

	long getMaxX();
	long getMaxY();
	long getMaxZ();

	vector< vector< vector<bool> > >* getCubes(void);

	vector<Point> getCube(unsigned x, unsigned y, unsigned z);
	void setCubeVal(unsigned x, unsigned y, unsigned z, bool val);
	bool getCubeVal(unsigned x, unsigned y, unsigned z);
};
	
#endif