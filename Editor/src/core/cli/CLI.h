#pragma once

#include "pybind11/embed.h"
namespace py = pybind11;

class CLI
{
public:

	static void parseArgs(int argc, char** argv);

	static CLI* getInstance() {
		if (!s_instance) s_instance = new CLI();
		return s_instance;
	}

	void init();
	static std::string getExecPath() { return s_exec_path; }
	static const std::string getCwd();
	static void chDir(const std::string& path);

private:
	CLI() {
		m_py_os = py::module::import("os");
	}
	static std::pair<std::string, std::string> getKeyValue(const std::string& line);
	static CLI* s_instance;
	static std::string s_exec_path;

	void readPeConfigFile();
	py::module m_py_os;
};
