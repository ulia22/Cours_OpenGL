#include "Point.h"


Point::Point()
{
    x=0.;
    y=0.;
    z=0.;
}

Point::Point(double px, double py, double pz)
{
    x=px;
    y=py;
    z=pz;
}

Point::Point(const Point& P)
{
    x=P.getX();
    y=P.getY();
    z=P.getZ();
}

Point::~Point()
{
    //dtor
}

double Point::getX()const{
    return x;
}

double Point::getY()const {
    return y;
}

double Point::getZ()const{
    return z;
}

void Point::setX(double px){
    x=px;
}

void Point::setY(double py){
    y=py;
}

void Point::setZ(double pz){
   z=pz;
}



Point Point::ProjectOnLine(Point Point1Line, Point Point2Line){ // attention direction vect
    Point *P= new Point();

    Vector *P12 = new Vector(Point2Line.getX()-Point1Line.getX(), Point2Line.getY()-Point1Line.getY(), Point2Line.getZ()-Point1Line.getZ());
    Vector *P1this = new Vector(getX()-Point1Line.getX(), getY()-Point1Line.getY(), getZ()-Point1Line.getZ());
    double n12= P12->Norme();

    double n1this=P1this->Scalar(*P12)/n12;

    P->setX(Point1Line.getX()+  P12->getX() * n1this);
    P->setY(Point1Line.getY()+  P12->getY() * n1this);
    P->setX(Point1Line.getZ()+  P12->getZ() * n1this);

    return *P;

}


Point Point::ProjectOnLine(Point Point1, Vector vecteur){
    Point *P= new Point();

    Vector *P1this = new Vector( getX()-Point1.getX(), getY()-Point1.getY(), getZ()-Point1.getZ());
	vecteur.Normalize();
    double n1this=P1this->Scalar(vecteur)/vecteur.Norme();

    P->setX(Point1.getX()+  vecteur.getX() * n1this);
    P->setY(Point1.getY()+  vecteur.getY() * n1this);
    P->setX(Point1.getZ()+  vecteur.getZ() * n1this);

    return *P;
}



Point Point::ProjectOnPlan(Point PointOnPlane, Vector NormalOfPlane){
    Point *P=new Point();
    Vector *V= new Vector( PointOnPlane.getX() - getX(),  PointOnPlane.getY() - getY(),  PointOnPlane.getZ() - getZ());
    double s= V->Scalar(NormalOfPlane);
    double n= NormalOfPlane.Norme();
    double m= s/n;

    P->setX(PointOnPlane.getX() - NormalOfPlane.getX() * m);
    P->setY(PointOnPlane.getY() - NormalOfPlane.getY() * m);
    P->setZ(PointOnPlane.getZ() - NormalOfPlane.getZ() * m);

    return *P;
}


void Point::AfficherPoint(){
	glPushMatrix();
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex3f(getX(),getY(),getZ());
	glEnd();
	glPopMatrix();
}

 Point Point::operator+(Point p1){
	return Point((getX()+p1.getX()),getY()+p1.getY(),getZ()+p1.getZ());
}

Point Point::operator+(Vector v1){
	return Point((getX()+v1.getX()),getY()+v1.getY(),getZ()+v1.getZ());
}

Point Point::operator*(double a){
	return Point((a*getX()),a*getY(),a*getZ());
}























