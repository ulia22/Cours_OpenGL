#include "Vector.h"
#include <math.h>

Vector::Vector(){

    x=0.;
    y=0.;
    z=0.;

}

Vector::Vector(double px, double py, double pz)
{
    x=px;
    y=py;
    z=pz;
}

Vector::~Vector()
{
    //dtor
}

Vector::Vector(const Vector& V)
{
    x=V.getX();
    y=V.getY();
    z=V.getZ();
}

double Vector::getX() const{
    return x;
}

double Vector::getY() const{
    return y;
}

double Vector::getZ() const{
    return z;
}

void Vector::setX( double px){
    x=px;
}

void Vector::setY(double py){
    y=py;
}

void Vector::setZ(double pz){
   z=pz;
}

double Vector::Norme(){
    return sqrt( getX()*getX() + getY()*getY()+ getZ()*getZ());
}


void Vector::Normalize(){
    double n=Norme();
    setX(getX()/n);
    setY(getY()/n);
    setZ(getZ()/n);
}


double Vector::Scalar(Vector Vector2){
    return getX()*Vector2.getX()+getY()*Vector2.getY()+getZ()*Vector2.getZ();
}


Vector Vector::Vectoriel(Vector Vector2){
    Vector *V= new Vector();
    V->setX( getY() * Vector2.getZ() - getZ() * Vector2.getY() );
    V->setY( getZ() * Vector2.getX() - getX() * Vector2.getZ() );
    V->setZ( getX() * Vector2.getY() - getY() * Vector2.getX() );
    return *V;
}


double Vector::Angle(Vector Vector2){// regarder les cos et sinus attention c'est en radient faire fonction en degres regarder acosf et PI
    double n1=Norme();
    double n2=Vector2.Norme();
    double S=Scalar(Vector2);
    Vector V= Vectoriel(Vector2); /// ici

    double cosA = acosf( S/( n1* n2));
    double sinA = asinf( V.Norme()/( n1* n2));

    if(sinA>0)
        return cosA;
    else
      return 2*M_PI-cosA;
}

void Vector::AfficherVector(Point p){
	glBegin(GL_LINES);
	glPointSize(2);
	glVertex3f(p.getX(),p.getY(),p.getZ());
	glVertex3f(p.getX()+ getX(),p.getY()+getY(),p.getZ()+getZ());
	glEnd();
}
Vector Vector::operator*(double a){
	return Vector((a*getX()),a*getY(),a*getZ());
}
