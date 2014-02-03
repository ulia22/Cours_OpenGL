///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synth�se d'images - Mod�lisation g�om�trique
// Auteur : Gilles Gesqui�re
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de cr�er des formes de bases.
// La forme repr�sent�e ici est un polygone blanc dessin� sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include <iostream>

//Tp
#include "Point.hpp"
#include "Hermite.hpp"


/* Dans les salles de TP, vous avez g�n�ralement acc�s aux glut dans C:\Dev. Si ce n'est pas le cas, t�l�chargez les .h .lib ...
Vous pouvez ensuite y faire r�f�rence en sp�cifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le r�pertoire courant, on aura alors #include "glut.h" 
*/

#include <GL/glut.h> 

// D�finition de la taille de la fen�tre
#define WIDTH  480
#define HEIGHT 480

// D�finition de la couleur de la fen�tre
#define RED   1
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27


// Ent�tes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
void myGlVertex(Point v);
void displayLine(Point p, Vector v);
void drawCurve(Point TabPointsOfCurve[], long nbPoints);

int main(int argc, char **argv) 
{  
  // initialisation  des param�tres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // d�finition et cr�ation de la fen�tre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carr�");

  // initialisation de OpenGL et de la sc�ne
  initGL();  
  init_scene();

  // choix des proc�dures de callback pour 
  // le trac� graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fen�tre
  glutReshapeFunc(&window_reshape);
  // la gestion des �v�nements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des �v�nements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque
GLvoid initGL() 
{
  glClearColor(RED, GREEN, BLUE, ALPHA);        
}

// Initialisation de la scene. Peut servir � stocker des variables de votre programme
// � initialiser
void init_scene()
{
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // C'est l'endroit o� l'on peut dessiner. On peut aussi faire appel
  // � une fonction (render_scene() ici) qui contient les informations 
  // que l'on veut dessiner
  render_scene();

  // trace la sc�ne grapnique qui vient juste d'�tre d�finie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fen�tre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport � la fen�tre.
  glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

  // toutes les transformations suivantes s�appliquent au mod�le de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;
  default:
    printf ("La touche %d n�est pas active.\n", key);
    break;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//D�finition de la couleur
 glColor3f(1.0, 1.0, 1.0);

  //  Nous cr�ons ici un polygone. Nous pourrions aussi cr�er un triangle ou des lignes. Voir ci-dessous les parties 
  // en commentaires (il faut commenter le bloc qui ne vous int�resse pas et d�commenter celui que vous voulez tester.

   // Cr�ation de deux lignes
/*	glBegin(GL_LINES);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(-1, 1, 0); 
	glEnd();*/
  
 // cr�ation d'un polygone

	/*glBegin(GL_POLYGON);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);
	glEnd();*/

	//glutSolidCube(2);

/*
// cr�ation d'un triangle
	glBegin(GL_TRIANGLES);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
	glEnd();
*/
/*	Point A(-3.0, -3.0, 0.0);
	Point B(3.0, 3.0, 0.0);
	Point C(-3.0, 3.0, 0.0);
	Point Cp = C.ProjectOnLine(A, B);

	glPointSize (5.0);

	glBegin(GL_POINTS);
		myGlVertex(A);
		myGlVertex(B);
	glEnd();

	glBegin(GL_LINES);
		myGlVertex(A);
		myGlVertex(B);
	glEnd();

	glBegin(GL_POINTS);
		myGlVertex(C);
	glEnd();

	glBegin(GL_POINTS);
		myGlVertex(Cp);
	glEnd();
*/
	Point A(-0.0, -0.0, 0.0);
	Point B(2.0, 0.0, 0.0);
	Vector v1(1.0, 1.0, 0.0);
	Vector v2(1.0, -1.0, 0.0);

	glPointSize (4.0);

	glBegin(GL_POINTS);
		myGlVertex(A);
		myGlVertex(B);
	glEnd();

	displayLine(A, v1);
	displayLine(B, v2);

	Hermite myCurve(A, v1, B, v2);
	Point curve[10];
	myCurve.HermiteCubicCurve(curve ,10);
	drawCurve(curve, 10);
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
