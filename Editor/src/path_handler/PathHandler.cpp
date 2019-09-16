#include "pch.h"
#include "PathHandler.h"


std::string PathHandler::s_exec_path;


void PathHandler::init()
{
	py::exec("import sys, os");

	char pBuf[1024];
#ifdef _WIN32
	int bytes = GetModuleFileName(NULL, pBuf, sizeof pBuf);
	// TODO:  assert bytes > 0
#elif __linux__
	char szTmp[32];
	sprintf(szTmp, "/proc/%d/exe", getpid());
	int bytes = MIN(readlink(szTmp, pBuf, len), len - 1);
	if (bytes >= 0)
		pBuf[bytes] = '\0';
#endif
	auto os = py::module::import("os");
	s_exec_path = os.attr("path").attr("dirname")(pe::__fixPath(pBuf)).cast<std::string>();
	py::exec(std::string("sys.path.append('").append(s_exec_path).append("')"));
}

const std::string PathHandler::getCwd() {
	char buff[1024];
	return getCurrentDir(buff, sizeof buff);
}
void PathHandler::chDir(const std::string& path) {
	changeDir(path.c_str());
	PE_CONSOLE_LOG("CWD: %s", getCwd().c_str());
}

