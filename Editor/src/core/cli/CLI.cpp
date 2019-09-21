#include "pch.h"
#include "CLI.h"
#include "FileTree.h"


CLI* CLI::s_instance = nullptr;
FileTree* FileTree::s_instance = nullptr;
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

std::pair<std::string, std::string> CLI::getKeyValue(const std::string& line) {
	auto dict = pe::split(line, '=');
	if (dict.size() < 2) return std::make_pair("","");
	std::string key = pe::__removeWiteSpace(dict[0]);
	std::string value = pe::__getValueString(dict[1]);
	return std::make_pair(key, value);
}

void CLI::readPeConfigFile() {
	
	std::ifstream init_file(CLI::getExecPath().append("/peconfig.init"));
	if (init_file.is_open()) {
		std::string line;
		while (std::getline(init_file, line)) {
			if (line[0] == '#') continue;

			if (line == std::string("file_format_icons:")) {
				while (std::getline(init_file, line)) {
					if (line == std::string("end")) break;
					auto key_value = CLI::getKeyValue(line);
					if (key_value.first == std::string("dir_close"))	{ Resources::Icons::DIR_CLOSED.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("dir_open"))		{ Resources::Icons::DIR_OPEN.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_unknown")) { Resources::Icons::_FILE_UNKNOWN.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_peproj"))	{ Resources::Icons::FILE_PEPROJ.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_text"))	{ Resources::Icons::FILE_TEXT.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_xml"))		{ Resources::Icons::FILE_XML.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_py"))		{ Resources::Icons::FILE_PY.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_pyc"))		{ Resources::Icons::FILE_PYC.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_cpp"))		{ Resources::Icons::FILE_CPP.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_h"))		{ Resources::Icons::FILE_H.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_png"))		{ Resources::Icons::FILE_PNG.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_ttf"))		{ Resources::Icons::FILE_TTF.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_bin"))		{ Resources::Icons::FILE_BIN.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_dll"))		{ Resources::Icons::FILE_DLL.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
					if (key_value.first == std::string("file_obj"))		{ Resources::Icons::FILE_OBJ.loadFromFile(CLI::getExecPath().append(key_value.second)); continue; }
				}
				continue;
			}

			auto key_value = CLI::getKeyValue(line);
			if (key_value.first != std::string("")) {
				if (key_value.first == std::string("py_path")) {
					py::exec(std::string("sys.path.append('").append(
						m_py_os.attr("path").attr("abspath")(CLI::getExecPath().append(key_value.second)).cast<std::string>()
					).append("')"));
				}
			}
		}
	}
}