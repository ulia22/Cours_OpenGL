#include "FromFile.hpp"
#include <iostream>
#include <fstream>
#include <GL/glut.h>
using namespace std;

FromFile::FromFile(){}

void FromFile::displayFileOFF(string path){
	ifstream fichier(path.c_str(), ios::in);

	long nbVertex=0;
	long nbTriangle=0;
	long nbArrete=0;

	string type;

	float x = 0.f, y = 0.f, z = 0.f;
	unsigned int sommet1 = 0, sommet2 = 0, sommet3 = 0;

	if(fichier){
		fichier >> type;
		fichier >> nbVertex;
		fichier >> nbTriangle;
		fichier >> nbArrete;
		cout << "Fichier de type " << type << " composé de "<<nbVertex<<" vertex, dont "<<nbTriangle<<" triangles, et "<<nbArrete<<" arretes."<<endl; 
		//On stocke tous les vertex
		GLfloat *vertex = new GLfloat[nbVertex*3];
		for(long i = 0; i < nbVertex; i++){
			fichier >> x;
			fichier >> y;
			fichier >> z;
			vertex[i*3 + 0] = x;
			vertex[i*3 + 1] = y;
			vertex[i*3 + 2] = z;
		}
			
		//On stocke tous les indices des sommets des triangles
		GLuint *triangles = new GLuint[(unsigned int)nbTriangle*(unsigned int)3];
		for(long i = 0; i < nbTriangle; i++){
			fichier >> sommet1;//Celui-la sert à enlever le "3" devant les indices...
			fichier >> sommet1;
			fichier >> sommet2;
			fichier >> sommet3;
			triangles[i*3 + 0] = sommet1;
			triangles[i*3 + 1] = sommet2;
			triangles[i*3 + 2] = sommet3;
		}
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glTranslatef(0, -0.15, 0);
		glVertexPointer(3, GL_FLOAT, 0, vertex);
		//glDrawElements(GL_TRIANGLES, nbTriangle*3, GL_UNSIGNED_INT, triangles);
		//glDrawElements(GL_LINE_STRIP, nbTriangle*3, GL_UNSIGNED_INT, triangles);
		
		for(long i = 0; i < nbTriangle; i++){
			glBegin(GL_LINE_STRIP);
				glVertex3f(vertex[triangles[i*3+0]*3+0], vertex[triangles[i*3+0]*3+1], vertex[triangles[i*3+0]*3+2]);
				glVertex3f(vertex[triangles[i*3+1]*3+0], vertex[triangles[i*3+1]*3+1], vertex[triangles[i*3+1]*3+2]);
				glVertex3f(vertex[triangles[i*3+2]*3+0], vertex[triangles[i*3+2]*3+1], vertex[triangles[i*3+2]*3+2]);
				glVertex3f(vertex[triangles[i*3+0]*3+0], vertex[triangles[i*3+0]*3+1], vertex[triangles[i*3+0]*3+2]);
			glEnd();
		}
		glDisableClientState(GL_VERTEX_ARRAY);
		delete[] vertex;
		delete[] triangles;
	}
	else{
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
}


