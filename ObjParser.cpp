#include "ObjParser.hpp"
#include <string.h>
#include <fstream>

bool ObjParser::parse(const char* filePath, Shape* shape) {
	std::ifstream fin;
	fin.open(filePath);
	if (!fin.good()) {
		return false;
	}

	std::string buf;
	S_VertexIndex vertexIndex = {0, 0, 0};
	m_sTextureFile[0] = '\0';
	while (std::getline(fin, buf)) {
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
			case 'm':
				if (buf.substr(0, 6) == "mtllib") {
					_parseMaterial(buf);
				}
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
			vertices[vertexIndex++] = m_vTextures[face.vertex[i].indexTexture - 1].x;
			vertices[vertexIndex++] = m_vTextures[face.vertex[i].indexTexture - 1].y;
			// faces
			elements[elementIndex] = elementIndex;
			++elementIndex;
		}
	}

	shape->setVertices(vertices, sizeof(vertices));
	shape->setElements(elements, sizeof(elements));
	if (m_sTextureFile != NULL) {
		shape->setTextureFile(std::string(m_sTextureFile));
	}
}

void ObjParser::_parseVertex(S_VertexIndex &vertexIndex, std::string line) {
	switch (line[1]) {
		// vertex line
		case ' ':
			float vertexX, vertexY, vertexZ;
			sscanf(line.c_str(), "v %f %f %f\n", &vertexX, &vertexY, &vertexZ);
			S_Vertex vertex;
			vertex.x = vertexX;
			vertex.y = vertexY;
			vertex.z = vertexZ;
			m_vVertices.push_back(vertex);
			break;
		case 't':
			float textureX, textureY;
			sscanf(line.c_str(), "vt %f %f\n", &textureX, &textureY);
			S_Texture texture;
			texture.x = textureX;
			texture.y = textureY;
			m_vTextures.push_back(texture);
			break;
		default:
			break;
	}
}

void ObjParser::_parseFace(std::string line) {
	S_Face face;
	int result = sscanf(
		line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
		&face.vertex[0].indexCoords, &face.vertex[0].indexTexture, &face.vertex[0].indexNormal,
		&face.vertex[1].indexCoords, &face.vertex[1].indexTexture, &face.vertex[1].indexNormal,
		&face.vertex[2].indexCoords, &face.vertex[2].indexTexture, &face.vertex[2].indexNormal
	);
	m_vFaces.push_back(face);
}

void ObjParser::_parseMaterial(std::string line) {
	char fileName[MAX_CHARS_PER_LINE];
	sscanf(line.c_str(), "mtllib %s\n", &fileName);
	std::ifstream fin;
	fin.open(std::string("./materials/") + fileName);
	if (!fin.good()) {
		return;
	}

	std::string buf;
	S_VertexIndex vertexIndex = {0, 0, 0};
	char key[10];
	while (std::getline(fin, buf)) {
		sscanf(buf.c_str(), "%s", &key);
		if (strstr(key, "map_Kd") != NULL) {
			sscanf(buf.c_str(), "map_Kd %s\n", &m_sTextureFile);
		}
	}
}
