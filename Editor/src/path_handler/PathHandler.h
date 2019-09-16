#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

class PathHandler
{
public:
	static void init();
	static const std::string& getExecPath() { return s_exec_path; }
	static const std::string getCwd();
	static void chDir( const std::string& path );

private:
	PathHandler();
	static std::string s_exec_path;
};
