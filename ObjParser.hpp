#ifndef __OBJ_PARSER__
#define __OBJ_PARSER__

#include <string>
#include <vector>

#define MAX_CHARS_PER_LINE 512

typedef struct {
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float textureX;
	float textureY;
} S_Vertex;

typedef struct {
	int indexCoords;
	int indexTexture;
	int indexNormal;

} S_VertexIndex;

class ObjParser {
	private:
	void _parseVertex(S_VertexIndex &index, char* line);
	std::vector<S_Vertex> m_vVertices;

	public:
	bool parse(const char*);
};

#endif
