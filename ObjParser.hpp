#ifndef __OBJ_PARSER__
#define __OBJ_PARSER__

#include <string>
#include <vector>
#include "Shape.hpp"

#define MAX_CHARS_PER_LINE 512

typedef struct {
	float x;
	float y;
	float z;
	float textureX;
	float textureY;
} S_Vertex;

typedef struct {
	int vertexIndex1;
	int vertexIndex2;
	int vertexIndex3;
} S_Face;

typedef struct {
	int indexCoords;
	int indexTexture;
	int indexNormal;

} S_VertexIndex;

class ObjParser {
	private:
	void _populateShape(Shape* shape);
	void _parseVertex(S_VertexIndex &index, char* line);
	void _parseFace(char* line);
	std::vector<S_Vertex> m_vVertices;
	std::vector<S_Face> m_vFaces;

	public:
	bool parse(const char* filePath, Shape* shape);
};

#endif
