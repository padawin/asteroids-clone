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
} S_Vertex;

typedef struct {
	float x;
	float y;
} S_Texture;

typedef struct {
	int indexCoords;
	int indexTexture;
	int indexNormal;
} S_VertexIndex;

typedef struct {
	S_VertexIndex vertex[3];
} S_Face;

class ObjParser {
	private:
	void _populateShape(Shape* shape);
	void _parseVertex(S_VertexIndex &index, std::string line);
	void _parseFace(std::string line);
	void _parseMaterial(std::string line);
	std::vector<S_Vertex> m_vVertices;
	std::vector<S_Texture> m_vTextures;
	std::vector<S_Face> m_vFaces;
	char m_sTextureFile[MAX_CHARS_PER_LINE];

	public:
	bool parse(const char* filePath, Shape* shape);
};

#endif
