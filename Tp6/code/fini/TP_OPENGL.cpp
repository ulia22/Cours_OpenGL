// 3Dtest1.cpp : définit le point d'entrée pour l'application console.
//

///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Modélisation géométrique
// Auteur : Gilles Gesquière
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de créer des formes de bases.
// La forme représentée ici est un polygone blanc dessiné sur un fond rouge
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "Point.h"
#include "Vector.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>


/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>.
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h"
*/

#include <GL/glut.h>//glut.h
//#include "glut.h"




// Définition de la taille de la fenêtre
#define WIDTH  480
#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   1
#define GREEN 0
#define BLUE  0
#define ALPHA 1



// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 32

#define KEY_PLUS 43
#define KEY_MOINS 45

double meridien;
double parallele;
double rayon;

/*#define KEY_DOWN 40
#define KEY_RIGHT 39
#define KEY_UP 38
#define KEY_LEFT 37
Point* tabRef;
int indice=0;

*/


using namespace std;

// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
void TP1();
void TP2();
void DrawCurve(Point TabPointsOfCurve[],long nbPoints);
Point* HermiteCubicCurve(Point p0, Point p1, Vector V0, Vector V1, long nbU);
int Factoriel (int n);
Point* BezierCurveByBernstein(Point TabControlPoint[],long nbControlPoint,long nbU);
Point* BezierCurveByCasteljau(Point TabControlPoint[], long nbControlPoint, long nbU);
void TP3();
Point** SurfaceRegle(Point P[],Point Q[],long U, long V);
void DrawCurveSurface(Point *TabPointsOfCurve[],long nbPointsU,long nbPointsV);
void TP4();
void DrawCylindre(Point* P,Point*Q, int taille);
void cylindre(double rayon, double hauteur, long meridien,Point* Pb,Point* Ph);
void DrawCone(Point *P,Point s,int taille);
Point* Cone(double rayon, double hauteur, long n);
void DrawSphere(Point **P,double parallele,double meridien);
Point** Sphere(double rayon, long meridien,long parallele);





int main(int argc, char **argv)
{
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carré");

  // initialisation de OpenGL et de la scène
  initGL();
  init_scene();



  // choix des procédures de callback pour
  // le tracé graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL()
{
  glClearColor(RED, GREEN, BLUE, ALPHA);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
	meridien=8;
	parallele=8;
	rayon=20;
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
  // à une fonction (render_scene() ici) qui contient les informations
  // que l'on veut dessiner
  render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est
  // de trop grosse taille par rapport à la fenêtre.
  glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
 //glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);

  // toutes les transformations suivantes s´appliquent au modèle de vue
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{
  switch (key) {
  case KEY_ESC:
    exit(1);
    break;
  case KEY_PLUS:
		meridien++;
		parallele++;
		//glColor3f(1., 1., 1.);
		cout<<"+  m "<<meridien<<" p "<<parallele<<endl;
		window_display();
		//Sphere(rayon,meridien,parallele);
		
		
		break;
  case KEY_MOINS:
	  if(meridien>3 && parallele>2){
		  meridien--;
		  parallele--;
		  cout<<"-  m "<<meridien<<" p "<<parallele<<endl;
		  window_display();
		  
	  }else
		  cout<<"impossible: meridien<3 ou parallele<2"<<endl;
	  
	  break;
/*case KEY_DOWN:
	tabRef[indice].setX(tabRef[indice].getX()+1);
	break;
case KEY_UP:
	tabRef[indice].setX(tabRef[indice].getX()-1);
	break; 
case KEY_RIGHT:
	tabRef[indice].setY(tabRef[indice].getY()+1);
	break;
case KEY_LEFT:
	tabRef[indice].setY(tabRef[indice].getY()-1);
	break; 
case 1:
		indice=1;break;
case 2:
		indice=2; break;
		*/

  default:
    printf ("La touche %d n'est pas active.\n", key);
    break;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//Définition de la couleur
 	
  //  Nous créons ici un polygone. Nous pourrions aussi créer un triangle ou des lignes. Voir ci-dessous les parties
  // en commentaires (il faut commenter le bloc qui ne vous intéresse pas et décommenter celui que vous voulez tester.

	
	//TP1();
	//TP2();
	//TP3();
	TP4();
	//TP5();
	
	// Création de deux lignes
	/*glBegin(GL_LINES);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(-1, 1, 0);
	glEnd();
*/
 // création d'un polygone
/*	glBegin(GL_POLYGON);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);
	glEnd();
*/


/*
// création d'un triangle
	glBegin(GL_TRIANGLES);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
	glEnd();
*/

}


void TP1(){ // tester sur plusieur
	
	//online p0 v
	glColor3f(1.0, 1.0, 1.0);

	Point p(1.,-1.,0);
	p.AfficherPoint();

	Point p0(-1.,-1.,0);
	p0.AfficherPoint();

	Vector v(2.,2.,0);
	v.AfficherVector(p0);

	glColor3f(0.1, 0.1, 1.0);
	Point n = p.ProjectOnLine(p0, v);
	n.AfficherPoint();
	/*
	//online p1 p2
	glColor3f(1.0, 1.0, 1.0);
	Point p(1.,-1.,0);
	p.AfficherPoint();
	
	Point p0(3.,2.,0);
	p.AfficherPoint();
	
	Point p1(-3.,-1.,0);
	p.AfficherPoint();
	
	glColor3f(0.1, 0.1, 1.0);
	Point n = p.ProjectOnLine(p0, p1);
	n.AfficherPoint();
	
	
	
	//onplane p0 n
	glColor3f(1.0, 1.0, 1.0);

	Point p(1.,-1.,0);
	p.AfficherPoint();

	Point p0(2.,1.,0);
	p0.AfficherPoint();

	Vector v(0.,0.,1.);
	v.AfficherVector(p0);

	glColor3f(0.1, 0.1, 1.0);
	Point n = p.ProjectOnLine(p0, v);
	n.AfficherPoint();
	*/
	
	
	// affichage de la projection
	glBegin(GL_LINES);
	glVertex3f(n.getX(),n.getY(),n.getZ());
	glVertex3f(p.getX(),p.getY(),p.getZ());
	glEnd();
	
	/*
	if(n.getX()< p0.getX() && n.getY() < p0.getY() && n.getZ()<= p0.getZ()){
		glBegin(GL_LINES);
		glVertex3f(p0.getX(),p0.getY(),p0.getZ());
		glVertex3f(n.getX(),n.getY(),n.getZ());
		glEnd();
	}
	else{
		glBegin(GL_LINES);
		glVertex3f(p0.getX(),p0.getY(),p0.getZ());
		glVertex3f(n.getX(),n.getY(),n.getZ());
		glEnd();
	}
	
	
	*/
	
	
	

	
}


void TP2(){
	glColor3f(1.0, 1.0, 1.0);

// exercice1:
/*	long n=5;
	Point *tab= new Point[n];
	Point p0(1.,1.,0.);
	Point p1(2.,1.,0.);
	Point p2(2.,2.,0.);
	Point p3(1.,2.,0.);
	tab[0]=p0;
	tab[1]=p1;
	tab[2]=p2;
	tab[3]=p3;
	tab[4]=p0;
	DrawCurve(tab,n);

*/
	Point Q0(0.,0.,0.);
	Point Q1(2.,0.,0.);
	Vector V0(1.,1.,0.);
	Vector V1(1.,-1.,0.);
	Q0.AfficherPoint();
	Q1.AfficherPoint();
	
	long n=5;
	HermiteCubicCurve(Q0,Q1,V0,V1,n);
	DrawCurve(HermiteCubicCurve(Q0,Q1,V0,V1,n),n+1);
	


	Point P0(-3.,-2.,0.);
	Point P1(-2.,-1.,0.);
	Point P2(-2.,0,0.);
	Point P3(0.,-1.,0.);
	P0.AfficherPoint();
	P1.AfficherPoint();
	P2.AfficherPoint();
	P3.AfficherPoint();
	Point Tab[4];
	Tab[0]=P0;
	Tab[1]=P1;
	Tab[2]=P2;
	Tab[3]=P3;
	//BezierCurveByBernstein(Tab,3,10);
	DrawCurve(BezierCurveByBernstein(Tab,4,8),9);

	Point p0(0.,1.,0.);
	Point p1(1.,2.,0.);
	Point p2(1.,3.,0.);
	Point p3(3.,2.,0.);
	glColor3f(1.0, 1.0, 1.0);
	p0.AfficherPoint();
	p1.AfficherPoint();
	p2.AfficherPoint();
	p3.AfficherPoint();
	Point Tab1[4];
	Tab1[0]=p0;
	Tab1[1]=p1;
	Tab1[2]=p2;
	Tab1[3]=p3;

	glColor3f(1.0, 1.0, 1.0);
	DrawCurve(Tab1,4);
	glColor3f(0.5, 0.5, 1.);
	BezierCurveByCasteljau(Tab1,4,5);
	DrawCurve(BezierCurveByCasteljau(Tab1,4,8),9);
	

	
}

void DrawCurve(Point TabPointsOfCurve[],long nbPoints){

	glBegin(GL_LINES);
	for(long i=0; i<(nbPoints-1);i++){
		glVertex3f(TabPointsOfCurve[i].getX(),TabPointsOfCurve[i].getY(),TabPointsOfCurve[i].getZ());
		glVertex3f(TabPointsOfCurve[i+1].getX(),TabPointsOfCurve[i+1].getY(),TabPointsOfCurve[i+1].getZ());
	}
	glEnd();

}

Point* HermiteCubicCurve(Point p0, Point p1, Vector V0, Vector V1, long nbU){

	double F0,F1,F2,F3;
	int j=0;
	Point *P= new Point[nbU+1];
	//P[0]=p0;
	//P[nbU]=p1;
	for(double i =0.; i<=1.;i+=1./(double)nbU){
		F0=2* pow(i,3) - 3* pow(i,2) +1;
		F1=-2*pow(i,3)+3*pow(i,2);
		F2=pow(i,3) -2* pow(i,2)+i;
		F3=pow(i,3)-pow(i,2);
		P[j]= p0*F0+p1*F1+V0*F2+V1*F3;
		j++;
	}
	return P;

}

int Factoriel (int n){
	if(n==0)
		return 1;
	else 
		return n*Factoriel(n-1);
}

//n+1 point de controle
Point* BezierCurveByBernstein(Point TabControlPoint[],long nbControlPoint,long nbU){
	Point *P= new Point[nbU+1];
	
	double *B= new double[nbControlPoint];
	int j=0;
	int n = nbControlPoint-1;
	for(double u=0.; u<=1.; u+=1./(double)nbU){
		for(int i=0;i<nbControlPoint;i++){
			B[i]=(double)Factoriel(n)/(double)(Factoriel(i)*Factoriel(n-i))*pow(u,i)*pow(1-u,n-i);
			P[j]= P[j]+TabControlPoint[i]*B[i];
		}
		j++;
	}
	P[nbU]=TabControlPoint[n];
	return P;
}

Point* BezierCurveByCasteljau(Point TabControlPoint[], long nbControlPoint, long nbU){
	Point *H=TabControlPoint;
	
	Point *Q= new Point[nbU+1];
	int n=nbControlPoint;
	
	int k=0;
	for(double u=0;u<=1;u+=1./nbU){
		Point *P= new Point[nbControlPoint-1];
		while(n>1){
			n=n-1;
			for(int j=0;j<n;j++)
			{
				P[j]= H[j]*(1-u)+H[j+1]*u;
			}
			glColor3f(0.5, 0.5, 0.0);
			DrawCurve(P,n);
			H=P;
			
		}
		//glColor3f(0., 0.5, 0.5);
		//H[0].AfficherPoint();
		Q[k]=H[0];
		H=TabControlPoint;
		n=nbControlPoint;
		k++;
	}
	glColor3f(1., 1., 1.);
	return Q;	
}



void TP3(){

	glColor3f(1., 1., 1.);
	Point P0(-3.,-2.,0.);
	Point P1(-2.,-1.,0.);
	Point P2(-2.,0,0.);
	Point P3(0.,-1.,0.);
	/*P0.AfficherPoint();
	P1.AfficherPoint();
	P2.AfficherPoint();
	P3.AfficherPoint();*/
	Point Tab[4];
	Tab[0]=P0;
	Tab[1]=P1;
	Tab[2]=P2;
	Tab[3]=P3;
	Point *P=BezierCurveByBernstein(Tab,4,8);
	DrawCurve(P,9);
	
	Point Q0(2.,-2.,0.);
	Point Q1(-1.,1.,0.);
	Point Q2(1.,-2,-1.);
	Point Q3(-1.,3.,-2.);
	/*Q0.AfficherPoint();
	Q1.AfficherPoint();
	Q2.AfficherPoint();
	Q3.AfficherPoint();*/
	Point Tab1[4];
	Tab1[0]=Q0;
	Tab1[1]=Q1;
	Tab1[2]=Q2;
	Tab1[3]=Q3;
	Point *Q=BezierCurveByBernstein(Tab1,4,8);
	
	glColor3f(1., 0.5, 0.5);
	Point **S=SurfaceRegle(P,Q,9,9);
	DrawCurveSurface(S,9,10);
	glColor3f(1., 1., 1.);
	DrawCurve(P,9);
	DrawCurve(Q,9);
	
}

void DrawCurveSurface(Point *TabPointsOfCurve[],long nbPointsU,long nbPointsV){
	/*glVertex3f(TabPointsOfCurve[0][0].getX(),TabPointsOfCurve[0][0].getY(),TabPointsOfCurve[0][0].getZ());
	glVertex3f(TabPointsOfCurve[0][1].getX(),TabPointsOfCurve[0][1].getY(),TabPointsOfCurve[0][1].getZ());*/

	glColor3f(1., 0.5, 0.5);
	
	for(long i=0; i<(nbPointsU-1);i++){
		glBegin(GL_LINE_STRIP);
		for(long j=0; j<(nbPointsV-1);j++){
			glVertex3f(TabPointsOfCurve[i][j].getX(),TabPointsOfCurve[i][j].getY(),TabPointsOfCurve[i][j].getZ());
			glVertex3f(TabPointsOfCurve[i+1][j].getX(),TabPointsOfCurve[i+1][j].getY(),TabPointsOfCurve[i+1][j].getZ());
			glVertex3f(TabPointsOfCurve[i][j+1].getX(),TabPointsOfCurve[i][j+1].getY(),TabPointsOfCurve[i][j+1].getZ());
		}
		glEnd();
	}
	
}

Point** SurfaceRegle(Point P[],Point Q[],long U, long V){
	glColor3f(0., 0., 0.);
	glBegin(GL_LINES);
	for(int i=0;i<U;i++){
		glVertex3f(P[i].getX(),P[i].getY(),P[i].getZ());
		glVertex3f(Q[i].getX(),Q[i].getY(),Q[i].getZ());
	}
	glEnd();
	
	int k;
	Point **S=new Point*[U];
	for(int i=0;i<U;i++)
		S[i]=new Point[V+1];
	cout<<"V   "<<V<<endl;
	
	for(int u=0;u<U;u++){
		k=0;
		//cout<<"    "<<u<<endl;
		//int u=0;
		for(float t=0;t<=1.;t+=1./V){
			S[u][k]=P[u]*(1-t)+Q[u]*t;
			cout<<"k:"<<k<<"   u: "<<u<<endl;
				//<<"   1-t:"<<(1-t)<<"   t: "<<t<<endl;
			glColor3f(0., 0.5, 1.);
			S[u][k].AfficherPoint();
			//glColor3f(0., 1., 0.);
			k++;
		}
	}
	return S;
}



void TP4(){
	glRotatef(45.f, 1.0f, 0.0f, 0.0f); 
	//glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

///////////exercice1:
	/*Point *Pb=new Point[10];
	Point *Ph=new Point[10];
	glColor3f(1., 1., 1.);
	cylindre(10,20,10,Pb,Ph);
	DrawCylindre(Pb,Ph,10);*/

//////////exercice2;
	/*Point S(0,0,20);
	glColor3f(0., 0., 0.);
	S.AfficherPoint();
	glColor3f(0.5, 0.5, 0.5);
	int n=10;
	Point *P=Cone(15,20,n);
	DrawCone(P,S,n);*/
	
	Point o(0,0,0);
	glColor3f(1., 1., 1.);
	o.AfficherPoint();
	
	//exercice3:
	glColor3f(0., 0., 0.);
	//Sphere(20,meridien,parallele);
	DrawSphere(Sphere(20,meridien,parallele),meridien,parallele);


}

void DrawCylindre(Point* P,Point*Q, int taille){
	glColor3f(0., 0., 0.);
	glBegin(GL_POLYGON);
	for(int i=0;i<taille;i++){
			glVertex3f(Q[i].getX(),Q[i].getY(),Q[i].getZ());
	}
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	int k,ksuiv,isuiv;
	for(int i=0;i<taille;i++){
		k=taille-i-1;
		ksuiv=k-1;
		isuiv=i+1;
		if(i==9 && k==0)
		{
			isuiv=0;
			ksuiv=9;
		}
			
		glBegin(GL_QUADS);
			glVertex3f(P[i].getX(),P[i].getY(),P[i].getZ());
			glVertex3f(Q[k].getX(),Q[k].getY(),Q[k].getZ());
			glVertex3f(Q[ksuiv].getX(),Q[ksuiv].getY(),Q[ksuiv].getZ());
			glVertex3f(P[isuiv].getX(),P[isuiv].getY(),P[isuiv].getZ());
			glVertex3f(P[i].getX(),P[i].getY(),P[i].getZ());
		glEnd();
	}
	
	glColor3f(0., 0., 0.);
	glBegin(GL_POLYGON);
	for(int i=0;i<taille;i++){
			glVertex3f(P[i].getX(),P[i].getY(),P[i].getZ());
	}
	glEnd();
}

void cylindre(double rayon, double hauteur, long meridien,Point *Pb,Point* Ph){

	float angle=2*M_PI /(float)meridien;
	//cout<<"  angle "<<angle<<endl;
	//double x=0,y=0;
	
	//x²+y²=r²
	//x=rcos(angle)
	//y=rsin(angle)
	//z=+-h/2
	//int k=0;
	for(int k =0;k<meridien;k++){

		double resultC= rayon*cosf(angle*k);
		float resultS=(float) rayon*((float)sinf(angle*k));
		//cout<<"  k  "<<k<<" x  "<<resultC<<"  y "<<resultS<<endl;
		Pb[k].setX(resultC);
		Pb[k].setY((double)resultS);
		Pb[k].setZ(-hauteur/2.);
		
		Ph[meridien-k-1].setX(resultC);
		Ph[meridien-k-1].setY(resultS);
		Ph[meridien-k-1].setZ(hauteur/2.);
		
	}
	//return P;
}

void DrawCone(Point *P,Point s,int taille){
	
	glColor3f(0.5, 0.5, 0.5);
	for(int i=0;i<taille;i++){	
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(s.getX(),s.getY(),s.getZ());
			glVertex3f(P[i].getX(),P[i].getY(),P[i].getZ());
			glVertex3f(P[i+1].getX(),P[i+1].getY(),P[i+1].getZ());
			
		glEnd();
	}
	
	glColor3f(0., 0., 0.);
	glBegin(GL_POLYGON);
	for(int i=0;i<taille;i++){
			glVertex3f(P[i].getX(),P[i].getY(),P[i].getZ());
	}
	glEnd();
}

Point* Cone(double rayon, double hauteur, long n){
	double angle = 2*M_PI/(double)n;
	Point *Pb=new Point[n];
	for(int k =0;k<n;k++){
		double x= rayon*cosf(angle*k);
		double y=rayon*sinf(angle*k);
		double z=0;
		Pb[k].setX(x);
		Pb[k].setY(y);
		Pb[k].setZ(z);
	}
	return Pb;
}


void DrawSphere(Point **P,double parallele,double meridien){
	
	//glColor3f(0.5, 0.5, 0.5);
	//float u=0.;
	for(int i=0;i<meridien;i++){
		for(int k=0;k<parallele;k++){
			//glColor3f(0., 0.5*u, 0.);
			glBegin(GL_LINES);	
			
			glVertex3f(P[i][k].getX(),P[i][k].getY(),P[i][k].getZ());
			glVertex3f(P[i][k+1].getX(),P[i][k+1].getY(),P[i][k+1].getZ());
			
			glVertex3f(P[i+1][k+1].getX(),P[i+1][k+1].getY(),P[i+1][k+1].getZ());
			glVertex3f(P[i+1][k].getX(),P[i+1][k].getY(),P[i+1][k].getZ());
			
			glVertex3f(P[i][k+1].getX(),P[i][k+1].getY(),P[i][k+1].getZ());
			glVertex3f(P[i+1][k+1].getX(),P[i+1][k+1].getY(),P[i+1][k+1].getZ());
			
			glVertex3f(P[i][k].getX(),P[i][k].getY(),P[i][k].getZ());
			glVertex3f(P[i+1][k].getX(),P[i+1][k].getY(),P[i+1][k].getZ());			
			
			glVertex3f(P[i+1][k+1].getX(),P[i+1][k+1].getY(),P[i+1][k+1].getZ());
			glVertex3f(P[i][k].getX(),P[i][k].getY(),P[i][k].getZ());

			glEnd();
			
		}
			
	}
}



Point** Sphere(double rayon, long meridien,long parallele){
	Point **P=NULL;
	if(meridien>=3 && parallele>=2){
		float teta=2*M_PI/(float)(meridien);
		float Phi=M_PI/(float)(parallele);

		/*
		x=rsin(phi)cos(teta)
		y=rsin(phi)sin(teta)
		z=rcos(phi)
		*/
		int taille=(int)(meridien+1)*(parallele+1);
		P=new Point*[(int)meridien];
		for(int i=0;i<meridien+1;i++)
			P[i]=new Point[(int)parallele+1];
		for(int i=0;i<=meridien;i++)
		{
			for(int k=0;k<=parallele;k++){
				P[i][k].setX(rayon*(sinf(Phi*k)*cosf(teta*i)));
				P[i][k].setY(rayon*(sinf(Phi*k)*sinf(teta*i)));
				P[i][k].setZ(rayon*cosf(Phi*k));
				P[i][k].AfficherPoint();
				if((P[i][k].getX()<=0 && P[i][k].getY()<=0) && (P[i][k].getZ()==-rayon || P[i][k].getZ()==rayon)){
					glColor3f(0.5, 0.5, 0.5);
					P[i][k].AfficherPoint();
					glColor3f(0., 0., 0.);
					}
			}

		}
	}
	return P;
}

