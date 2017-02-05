#ifndef __SHAPE__
#define __SHAPE__

#include <GL/glew.h>
#include <string>

class Shape {
	protected:
	GLfloat *m_fVertices;
	GLuint *m_iElements;
	std::string m_sTextureFile = "";
	unsigned long m_iNbVertices;
	unsigned long m_iNbElements;

	public:
	void setVertices(GLfloat *vertices, unsigned long nbVertices);
	void setElements(GLuint *elements, unsigned long nbElements);
	void setTextureFile(std::string file);
	~Shape();
	GLfloat *getVertices();
	GLuint *getElements();
	unsigned long getNbVertices();
	unsigned long getNbElements();
	std::string getTextureFile();
};

#endif
