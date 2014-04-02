#include "FromFile.hpp"
#include <iostream>
#include <fstream>

using namespace std;

FromFile::FromFile(){
	nbTriangle = 0;

}

void FromFile::displayFileOFF(string path){
	ifstream fichier(path.c_str(), ios::in);

	long nbVertex=0;
	long nbArrete=0;

	string type;

	fpath = path;
	float x = 0.f, y = 0.f, z = 0.f;
	unsigned int sommet1 = 0, sommet2 = 0, sommet3 = 0;

	if(fichier){
		fichier >> type;
		fichier >> nbVertex;
		fichier >> nbTriangle;
		fichier >> nbArrete;
		cout << "Fichier de type " << type << " composé de "<<nbVertex<<" vertex, dont "<<nbTriangle<<" triangles, et "<<nbArrete<<" arretes."<<endl; 
		//On stocke tous les vertex
		vertex = new GLfloat[nbVertex*3];
		for(long i = 0; i < nbVertex; i++){
			fichier >> x;
			fichier >> y;
			fichier >> z;
			vertex[i*3 + 0] = x;
			vertex[i*3 + 1] = y;
			vertex[i*3 + 2] = z;
		}
			
		//On stocke tous les indices des sommets des triangles
		triangles = new GLuint[(unsigned int)nbTriangle*(unsigned int)3];
		for(long i = 0; i < nbTriangle; i++){
			fichier >> sommet1;//Celui-la sert à enlever le "3" devant les indices...
			fichier >> sommet1;
			fichier >> sommet2;
			fichier >> sommet3;
			triangles[i*3 + 0] = sommet1;
			triangles[i*3 + 1] = sommet2;
			triangles[i*3 + 2] = sommet3;
		}
	}
	else{
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
}

//Indice tableau == numero du triangle
//i*3+0 = 1er voisin
//i*3+1 = 2e voisin 
//i*3+2 = 3e voisin
void computeNeighbour(void){
	triangleNeighbour = new unsigned int[3*nbTriangle];

}

GLfloat* FromFile::getVertex(void){return vertex;}
GLuint* FromFile::getTriangles(void){return triangles;}
long FromFile::getNbTriangle(void){return nbTriangle;}
string FromFile::getFPath(void){return fpath;}

unsigned int* getTriangleNeighbour(void){return triangleNeighbour;}