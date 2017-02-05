#ifndef __SHAPE_COLLECTION__
#define __SHAPE_COLLECTION__

#include <map>
#include <vector>
#include "ShapeFactory.hpp"
#include "Shape.hpp"

class ShapeCollection {
	protected:
	unsigned long m_lVerticesSize;
	unsigned long m_lElementsSize;
	std::map<ShapeType, GLuint> m_mVertexArrays;
	std::map<ShapeType, Shape*> m_mShapes;
	std::map<ShapeType, unsigned long> m_mShapesOffsets;
	GLuint m_iVertexBuffer;
	GLuint m_iElementBuffer;
	void _bindVertexArray(ShapeType type);
	void _bindTexture(ShapeType type, std::map<std::string, GLuint> textures);

	public:
	ShapeCollection() : m_lVerticesSize(0), m_lElementsSize(0) {}
	void addShape(ShapeType shapeType);
	void generateBuffers();
	void generateVertexArrays(GLuint shaderProgram);
	void clean();
	void bind(ShapeType type, std::map<std::string, GLuint> textures);
	void render(ShapeType type);
};

#endif
