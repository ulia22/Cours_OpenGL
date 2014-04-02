#ifndef FROMFILE_HPP
#define FROMFILE_HPP
#include <string>
#include <GL/glut.h>

using namespace std;

class FromFile
{
private:
	GLfloat *vertex;
	GLuint *triangles;
	unsigned int* triangleNeighbour;

	long nbTriangle;
	string fpath;
public:
	FromFile();

	void displayFileOFF(string path);

	GLfloat* getVertex(void);
	GLuint* getTriangles(void);
	void computeNeighbour(void);

	unsigned int* getTriangleNeighbour(void);

	long getNbTriangle(void);
	string getFPath(void);
};
#endif
