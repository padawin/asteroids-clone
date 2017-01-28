#include "ObjParser.hpp"
#include <fstream>
#include <sstream>

bool ObjParser::parse(const char* filePath) {
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
				break;
			default:
				break;
		}
	}

	return true;
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
