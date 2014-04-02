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
	long nbTriangle;
	string fpath;
public:
	FromFile();

	void displayFileOFF(string path);

	GLfloat* getVertex(void);
	GLuint* getTriangles(void);
	long getNbTriangle(void);
	string getFPath(void);
};
#endif
