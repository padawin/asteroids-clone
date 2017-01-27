#ifndef __OBJ_PARSER__
#define __OBJ_PARSER__

#include <string>

#define MAX_CHARS_PER_LINE 512

class ObjParser {
	private:
	void _parseVertex(char* line);

	public:
	bool parse(const char*);
};

#endif
