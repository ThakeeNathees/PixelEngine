#include "pch.h"
#include "CLI.h"


CLI* CLI::s_instance = nullptr;
std::string CLI::s_exec_path;

void CLI::init()
{
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

	readPeConfigFile();
}

const std::string CLI::getCwd() {
	char buff[1024];
	return getCurrentDir(buff, sizeof buff);
}

void CLI::chDir(const std::string& path) {
	changeDir(path.c_str());
	PE_CONSOLE_LOG("CWD: %s", getCwd().c_str());
}


void CLI::parseArgs(int argc, char** argv){
	//	TODO: parse args
}


//////////////////////////////////////////////////////////////////////////

void CLI::readPeConfigFile() {
	std::ifstream init_file("peconfig.init");
	if (init_file.is_open()) {
		std::string line;
		while (std::getline(init_file, line)) {
			auto dict = pe::split(line, '=');
			if (dict.size() >= 2) {
				std::string key = pe::__removeWiteSpace(dict[0]);
				std::string value = pe::__getValueString(dict[1]);
				if (key == std::string("py_path")) {
					py::exec(std::string("sys.path.append('").append(value).append("')"));
				}
			}
		}
	}
}