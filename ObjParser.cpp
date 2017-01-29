#include "ObjParser.hpp"
#include <fstream>
#include <sstream>

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
	std::stringstream ss(line);
	switch (line[1]) {
		// vertex line
		case ' ':
			char type[2];
			float vertexX, vertexY, vertexZ;
			ss >> type;
			ss >> vertexX;
			ss >> vertexY;
			ss >> vertexZ;
			if (vertexIndex.indexCoords >= m_vVertices.size()) {
				S_Vertex vertex;
				vertex.x = vertexX;
				vertex.y = vertexY;
				vertex.z = vertexZ;
				m_vVertices.push_back(vertex);
				vertexIndex.indexCoords++;
			}
			else {
				m_vVertices[vertexIndex.indexCoords].x = vertexX;
				m_vVertices[vertexIndex.indexCoords].y = vertexY;
				m_vVertices[vertexIndex.indexCoords].z = vertexZ;
			}
			break;
		default:
			break;
	}
}

void ObjParser::_parseFace(char* line) {
	std::stringstream ss(line);
	char type;
	char separator;
	int garbage;
	// format:
	// f \d+/\d+/\d+ \d+/\d+/\d+ \d+/\d+/\d+
	// The first int of each part interests us here
	S_Face face;
	ss >> type;
	ss >> face.vertexIndex1;ss >> separator;ss >> garbage;ss >> separator;ss >> garbage;
	ss >> face.vertexIndex2;ss >> separator;ss >> garbage;ss >> separator;ss >> garbage;
	ss >> face.vertexIndex3;ss >> separator;ss >> garbage;ss >> separator;ss >> garbage;
	m_vFaces.push_back(face);
}
