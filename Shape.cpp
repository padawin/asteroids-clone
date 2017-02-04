#include "Shape.hpp"
#include <stdlib.h>
#include <string.h>

Shape::~Shape() {
	free(m_fVertices);
	free(m_iElements);
}

void Shape::setVertices(GLfloat *vertices, unsigned long nbVertices) {
	m_fVertices = (GLfloat*) malloc(nbVertices * sizeof(GLfloat));
	m_iNbVertices = nbVertices;
	memcpy(m_fVertices, vertices, nbVertices);
}

void Shape::setElements(GLuint *elements, unsigned long nbElements) {
	m_iElements = (GLuint*) malloc(nbElements * sizeof(GLfloat));
	m_iNbElements = nbElements;
	memcpy(m_iElements, elements, nbElements);
}

void Shape::setTextureFile(std::string file) {
	m_sTextureFile = file;
}

GLfloat *Shape::getVertices() {
	return m_fVertices;
}
GLuint *Shape::getElements() {
	return m_iElements;
}

unsigned long Shape::getNbVertices() {
	return m_iNbVertices;
}

unsigned long Shape::getNbElements() {
	return m_iNbElements;
}

std::string Shape::getTextureFile() {
	return m_sTextureFile;
}
