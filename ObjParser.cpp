#include "ObjParser.hpp"
#include <string.h>
#include <fstream>

bool ObjParser::parse(const char* filePath, Shape* shape) {
	std::ifstream fin;
	fin.open(filePath);
	if (!fin.good()) {
		return false;
	}

	char buf[MAX_CHARS_PER_LINE];
	S_VertexIndex vertexIndex = {0, 0, 0};
	while (fin.getline(buf, MAX_CHARS_PER_LINE)) {
		if (buf[0] == '\0' || buf[0] == '#') {
			continue;
		}
		switch (buf[0]) {
			case 'v':
				_parseVertex(vertexIndex, buf);
				break;
			case 'f':
				_parseFace(buf);
				break;
			default:
				break;
		}
	}

	_populateShape(shape);
	return true;
}

void ObjParser::_populateShape(Shape* shape) {
	GLfloat vertices[m_vVertices.size() * 8];
	int j = 0;
	for (std::vector<S_Vertex>::size_type i = 0; i < m_vVertices.size(); ++i) {
		vertices[j++] = m_vVertices[i].x;
		vertices[j++] = m_vVertices[i].y;
		vertices[j++] = m_vVertices[i].z;
		vertices[j++] = 68.0f;
		vertices[j++] = 68.0f;
		vertices[j++] = 68.0f;
		vertices[j++] = 0.0f;
		vertices[j++] = 0.0f;
	}

	GLuint elements[m_vFaces.size() * 3];
	j = 0;
	for (std::vector<S_Face>::size_type i = 0; i < m_vFaces.size(); ++i) {
		elements[j++] = m_vFaces[i].vertexIndex1 - 1;
		elements[j++] = m_vFaces[i].vertexIndex2 - 1;
		elements[j++] = m_vFaces[i].vertexIndex3 - 1;
	}

	shape->setVertices(vertices, sizeof(vertices));
	shape->setElements(elements, sizeof(elements));
}

void ObjParser::_parseVertex(S_VertexIndex &vertexIndex, char* line) {
	switch (line[1]) {
		// vertex line
		case ' ':
			float vertexX, vertexY, vertexZ;
			sscanf(line, "v %f %f %f\n", &vertexX, &vertexY, &vertexZ);
			if (vertexIndex.indexCoords >= m_vVertices.size()) {
				S_Vertex vertex;
				vertex.x = vertexX;
				vertex.y = vertexY;
				vertex.z = vertexZ;
				m_vVertices.push_back(vertex);
			}
			else {
				m_vVertices[vertexIndex.indexCoords].x = vertexX;
				m_vVertices[vertexIndex.indexCoords].y = vertexY;
				m_vVertices[vertexIndex.indexCoords].z = vertexZ;
			}
			vertexIndex.indexCoords++;
			break;
		default:
			break;
	}
}

void ObjParser::_parseFace(char* line) {
	S_Face face;
	int texture1, texture2, texture3, normal1, normal2, normal3;
	sscanf(
		line, "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
		&face.vertexIndex1, &texture1, &normal1,
		&face.vertexIndex2, &texture2, &normal2,
		&face.vertexIndex3, &texture3, &normal3
	);
	m_vFaces.push_back(face);
}
