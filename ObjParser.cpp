#include "ObjParser.hpp"
#include <fstream>
#include <sstream>

bool ObjParser::parse(const char* filePath) {
	std::ifstream fin;
	fin.open(filePath);
	if (!fin.good()) {
		return false;
	}

	// read each line of the file
	while (!fin.eof()) {
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		fin.getline(buf, MAX_CHARS_PER_LINE);
		if (buf[0] == '\0' || buf[0] == '#') {
			continue;
		}
	}

	return true;
}
