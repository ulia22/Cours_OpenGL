#include "SurfaceParam.hpp"


SurfaceParam::SurfaceParam(){this->setNbParall(10);}
SurfaceParam::SurfaceParam(vector<Point> _bezier1, vector<Point> _bezier2, int _nbParall){
	this->setBezier1(_bezier1);
	this->setBezier2(_bezier2);
	this->setNbParall(_nbParall);
}
SurfaceParam::SurfaceParam(const SurfaceParam& s){
	bezier1 = s.bezier1;
	bezier2 = s.bezier2;
	parall = s.parall;
	nbParall = s.nbParall;
}


/*
	Getters and setters
*/
vector<Point> SurfaceParam::getBezier1(void){return bezier1;}
vector<Point> SurfaceParam::getBezier2(void){return bezier2;};
vector<vector<Point> > SurfaceParam::getParall(void){return parall;}
int SurfaceParam::getNbParall(void){return nbParall;}

void SurfaceParam::setBezier1(vector<Point> _b1){bezier1 = _b1;}
void SurfaceParam::setBezier2(vector<Point> _b2){bezier2 = _b2;}
void SurfaceParam::setParall(vector<vector<Point> > _par){parall = _par;}
void SurfaceParam::setNbParall(int _nb){nbParall = nbParall;}