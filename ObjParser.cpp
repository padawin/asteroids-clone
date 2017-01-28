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
				_parseVertex(buf);
				break;
			case 'f':
				break;
			default:
				break;
		}
	}

	return true;
}

void ObjParser::_parseVertex(char* line) {
}
