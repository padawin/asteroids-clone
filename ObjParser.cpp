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
	GLfloat vertices[m_vFaces.size() * 3 * 8];
	GLuint elements[m_vFaces.size() * 3];
	int vertexIndex = 0, elementIndex = 0;
	for (auto face : m_vFaces) {
		for (int i= 0; i < 3; ++i) {
			// vertex coordinates
			vertices[vertexIndex++] = m_vVertices[face.vertex[i].indexCoords - 1].x;
			vertices[vertexIndex++] = m_vVertices[face.vertex[i].indexCoords - 1].y;
			vertices[vertexIndex++] = m_vVertices[face.vertex[i].indexCoords - 1].z;
			// vertex color
			vertices[vertexIndex++] = 68.0f;
			vertices[vertexIndex++] = 68.0f;
			vertices[vertexIndex++] = 68.0f;
			// vertex texture
			vertices[vertexIndex++] = 0.0f;
			vertices[vertexIndex++] = 0.0f;
			// faces
			elements[elementIndex] = elementIndex;
			++elementIndex;
		}
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
			S_Vertex vertex;
			vertex.x = vertexX;
			vertex.y = vertexY;
			vertex.z = vertexZ;
			m_vVertices.push_back(vertex);
			break;
		default:
			break;
	}
}

void ObjParser::_parseFace(char* line) {
	S_Face face;
	sscanf(
		line, "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
		&face.vertex[0].indexCoords, &texture1, &normal1,
		&face.vertex[1].indexCoords, &texture2, &normal2,
		&face.vertex[2].indexCoords, &texture3, &normal3
	);
	m_vFaces.push_back(face);
}
