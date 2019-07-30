#include "pch.h"
#include "console.h"


int exec(std::string& result, const char* cmd) { // if success return 0;
	char buffer[128];
	result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) return 1;
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		return 2;
	}
	_pclose(pipe);
	return 0;
}



