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
#include <math.h>
#include <iostream>
#include <vector>

//Tp
#include "Point.hpp"
#include "Hermite.hpp"
#include "Casteljau.hpp"
#include "Bezier.hpp"
#include "SurfaceParam.hpp"
#include "Sphere.hpp"
#include "Box.hpp"
#include "FromFile.hpp"


/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h" 
*/

#include <GL/glut.h> 

// Définition de la taille de la fenêtre
#define WIDTH  480
#define HEIGHT 480

#define ORTHO_X_L -0.11
#define ORTHO_X_U 0.11
#define ORTHO_Y_L -0.11
#define ORTHO_Y_U 0.11
#define ORTHO_Z_L -0.11
#define ORTHO_Z_U 0.11

// Définition de la couleur de la fenêtre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27

using namespace std;

// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
void myGlVertex(Point v);
void displayLine(Point p, Vector v);
void drawCurve(Point TabPointsOfCurve[], long nbPoints);
void drawCurve(vector<Point> points);
void myMouse (int button, int state, int x, int y);

vector<Point> pts;
Point* selected;
double* rotate;

FromFile file;

int main(int argc, char **argv) 
{ 

	rotate = new double[4];
	rotate[0] = 0.0;
	rotate[1] = 0.0;
	rotate[2] = 0.0;
	rotate[3] = 0.0;
	file = FromFile();
	
	file.displayFileOFF(argv[1]);
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

  //Mouse
  //glutMouseFunc(&myMouse);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();

  return 0;
}//*/

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL() 
{

  glClearColor(RED, GREEN, BLUE, ALPHA);    
  glEnable(GL_DEPTH_TEST);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{


}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  int MatSpec [4] = {1,1,1,1};
  glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec); 
  
  //glEnable(GL_LIGHTING); 	// Active l'éclairage
  glEnable(GL_LIGHT0);
  
  glLoadIdentity();
  
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_CULL_FACE);
	
	
	
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


 // glOrtho(ORTHO_X_L, ORTHO_X_U, ORTHO_Y_L, ORTHO_Y_U, ORTHO_Z_L, ORTHO_Z_U);
	if(file.getFPath() == "../buddha.off"){
		glOrtho(ORTHO_X_L, ORTHO_X_U, ORTHO_Y_L, ORTHO_Y_U, ORTHO_Z_L, ORTHO_Z_U);
	}else if (file.getFPath() == "../max.off"){
		glOrtho(-150.0, 150.0, -150.0, 150.0, -1500.0, 1500.0);
	}

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{ 
  rotate[2] = 1.0;
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;

  case GLUT_KEY_UP:
  break;

  case GLUT_KEY_DOWN:
  break;

  case  GLUT_KEY_LEFT:
  	rotate[0]++;
  	cout << "ttest"<<endl;
  break;

  case GLUT_KEY_RIGHT:
  	rotate[0]--;
  break;

  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//Définition de la couleur
	glColor3f(0.0, 0.0, 1.0);

	GLfloat* v = file.getVertex();
	GLuint* t = file.getTriangles();

	if(file.getFPath() == "../buddha.off"){
		glTranslatef(0, -0.15, 0);
		glRotatef(60.0, 0.0, 1.0, 0.0);
	}else if (file.getFPath() == "../max.off"){
		glTranslatef(22, 0.0, 0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v);
	glDrawElements(GL_TRIANGLES, file.getNbTriangle()*3, GL_UNSIGNED_INT, t);
	glDisableClientState(GL_VERTEX_ARRAY);

}

void myGlVertex(Point v){
	glVertex3f(v.getX(), v.getY(), v.getZ());
}

void displayLine(Point p, Vector v){
	Point p1(p);

	glBegin(GL_LINES);
		myGlVertex(p1);
		myGlVertex(Point(p1.getX() + v.getX(), p1.getY() + v.getY(), p1.getZ() + v.getZ()));
	glEnd();
}

void drawCurve(Point TabPointsOfCurve[], long nbPoints){
	int i;
	glBegin(GL_LINE_STRIP);
	for(i = 0; i < nbPoints; ++i){
		myGlVertex(TabPointsOfCurve[i]);
	}
	glEnd();
}

void drawCurve(vector<Point> points){
	glBegin(GL_LINE_STRIP);
	for(unsigned int i = 0; i < points.size(); ++i){
		myGlVertex(points[i]);
	}
	glEnd();
}


void myMouse (int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		double ortho_M_X, ortho_M_Y;
		ortho_M_X = (double)x - (double)WIDTH / 2.0;
		ortho_M_Y = (double)y - (double)HEIGHT / 2.0;

		ortho_M_X < 0 ? ortho_M_X = (ortho_M_X * -3.0)/((double)WIDTH / 2.0) : ortho_M_X = (ortho_M_X * 3.0)/((double)WIDTH / 2.0);
		ortho_M_Y < 0 ? ortho_M_Y = (ortho_M_Y * -3.0)/((double)WIDTH / 2.0) : ortho_M_Y = (ortho_M_Y * 3.0)/((double)WIDTH / 2.0);

		cout << "X = " << ortho_M_X << " Y = " << ortho_M_Y << endl;
		double dist = 0;
		for(unsigned int i = 0; i < pts.size(); i++){
			dist = sqrt(pow(pts.at(i).getX() - ortho_M_X, 2) + pow(pts.at(i).getY() - ortho_M_Y, 2));
			cout << "Distance " << dist <<endl;
			if(dist <= 0.5){
				selected = &pts.at(i);
				break;
			}
		}
	}

	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		double ortho_M_X, ortho_M_Y;
		ortho_M_X = (double)x - (double)WIDTH / 2.0;
		ortho_M_Y = (double)y - (double)HEIGHT / 2.0;

		ortho_M_X < 0 ? ortho_M_X = (ortho_M_X * -3.0)/((double)WIDTH / 2.0) : ortho_M_X = (ortho_M_X * 3.0)/((double)WIDTH / 2.0);
		ortho_M_Y < 0 ? ortho_M_Y = (ortho_M_Y * -3.0)/((double)WIDTH / 2.0) : ortho_M_Y = (ortho_M_Y * 3.0)/((double)WIDTH / 2.0);
		cout << "X = " << ortho_M_X << " Y = " << ortho_M_Y << endl;

		if(selected != NULL){
			selected->setX(ortho_M_X);
			selected->setY(ortho_M_Y);
			selected = NULL;

			window_display();
		}
	}
}
