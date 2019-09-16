#pragma once

#include "pybind11/embed.h"
namespace py = pybind11;

class CLI
{
public:
	// cli return value
	enum class CliRet {
		Done = 0,		// exit the programe
		Success,
		PRJ_NOT_FOUNT, // project file not found
		Error,
	};

	static CliRet parseArgs(int argc, char** argv);

	static CLI* getInstance() {
		if (!s_instance) s_instance = new CLI();
		return s_instance;
	}

private:
	CLI() {}
	static CLI* s_instance;
};
