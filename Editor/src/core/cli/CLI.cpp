#include "pch.h"
#include "CLI.h"

#include "..//Resources.h"

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
	m_py_os = py::module::import("os");
	s_exec_path = m_py_os.attr("path").attr("dirname")(pe::__fixPath(pBuf)).cast<std::string>();
	py::exec(std::string("sys.path.append('").append(s_exec_path).append("')"));

	readPeConfigFile();

	m_py_proj_init = py::module::import("init");
}

const std::string CLI::getCwd() {
	char buff[1024];
	return getCurrentDir(buff, sizeof buff);
}

void CLI::chDir(const std::string& path) {
	changeDir(path.c_str());
	PE_CONSOLE_LOG("CWD: %s", getCwd().c_str());
}



int CLI::readTextFile(std::string& out, const std::string& path) {
	std::ifstream in(path);
	if (in.good())
	{
		std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		out = str;
		return 0;
	}
	return 1;
}

int CLI::readBinaryFile(std::vector<unsigned char>& buffer, const std::string& path) {
	std::ifstream in(path.c_str(), std::ios::binary );
	if (in.good()) {
		std::vector<unsigned char> new_buffer(std::istreambuf_iterator<char>(in), {});
		buffer = new_buffer;
		return 0;
	}
	return 1;
}


void CLI::parseArgs(int argc, char** argv){
	//	TODO: parse args
}

//////////////////////////////////////////////////////////////////////////

std::pair<std::string, std::vector<std::string>> CLI::getKeyValue(const std::string& line) {
	auto dict = pe::split(line, '=');
	std::vector<std::string> values;
	if (dict.size() < 2) return std::make_pair("",values);
	std::string key = pe::__removeWiteSpace(dict[0]);
	std::vector<std::string> __values = pe::split(dict[1], ',');
	for (int i = 0; i < __values.size(); i++) {
		values.push_back(pe::__getValueString(__values[i]));
	}
	return std::make_pair(key, values);
}

void CLI::save(const std::string& text_to_save, const std::string& file_path)
{
	std::ofstream save_file;
	save_file.open(file_path);
	save_file << text_to_save;
	save_file.close();
}


void CLI::readPeConfigFile() {
	
	std::ifstream init_file(CLI::getExecPath().append("/peconfig.init"));
	if (init_file.is_open()) {
		std::string line;
		while (std::getline(init_file, line)) {
			if (line[0] == '#') continue;
			auto key_value = CLI::getKeyValue(line);

			if (key_value.first == std::string("logo_path")) { Resources::LOGO.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }

			if (pe::__removeWiteSpace(line) == std::string("paths:")) {
				while (std::getline(init_file, line)) {
					if (pe::__removeWiteSpace(line) == std::string("end")) break;
					key_value = CLI::getKeyValue(line);
					if (key_value.first == std::string("py_path")) {
						py::exec(std::string("sys.path.append('").append(
							m_py_os.attr("path").attr("abspath")(CLI::getExecPath().append(key_value.second[0])).cast<std::string>()
						).append("')"));
					}
				}
				continue;
			}

			if (pe::__removeWiteSpace(line) == std::string("fonts:")) {
				while (std::getline(init_file, line)) {
					if (pe::__removeWiteSpace(line) == std::string("end")) break;
					key_value = CLI::getKeyValue(line);
					if (key_value.first == std::string("programming")) {
						auto font = ImGui::GetIO().Fonts->AddFontFromFileTTF(CLI::getExecPath().append(key_value.second[0]).c_str(), std::stof(key_value.second[1]));
						ImGui::SFML::UpdateFontTexture();
						Resources::Fonts::PROGRAMMING = font; continue;
					}
				}
				continue;
			}

			if (pe::__removeWiteSpace(line) == std::string("file_format_icons:")) {
				while (std::getline(init_file, line)) {
					if (pe::__removeWiteSpace(line)== std::string("end")) break;
					key_value = CLI::getKeyValue(line);
					if (key_value.first == std::string("dir_close"))	{ Resources::FileFormatIcons::DIR_CLOSED.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("dir_open"))		{ Resources::FileFormatIcons::DIR_OPEN.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_unknown")) { Resources::FileFormatIcons::_FILE_UNKNOWN.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_peproj"))	{ Resources::FileFormatIcons::FILE_PEPROJ.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_text"))	{ Resources::FileFormatIcons::FILE_TEXT.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_xml"))		{ Resources::FileFormatIcons::FILE_XML.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_py"))		{ Resources::FileFormatIcons::FILE_PY.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_pyc"))		{ Resources::FileFormatIcons::FILE_PYC.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_cpp"))		{ Resources::FileFormatIcons::FILE_CPP.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_h"))		{ Resources::FileFormatIcons::FILE_H.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_hpp"))		{ Resources::FileFormatIcons::FILE_HPP.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_png"))		{ Resources::FileFormatIcons::FILE_PNG.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_ttf"))		{ Resources::FileFormatIcons::FILE_TTF.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_bin"))		{ Resources::FileFormatIcons::FILE_BIN.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_dll"))		{ Resources::FileFormatIcons::FILE_DLL.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("file_obj"))		{ Resources::FileFormatIcons::FILE_OBJ.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
				}
				continue;
			}

			if (pe::__removeWiteSpace(line) == std::string("menu_icons:")) {
				while (std::getline(init_file, line)) {
					if (pe::__removeWiteSpace(line) == std::string("end")) break;
					key_value = CLI::getKeyValue(line);
					if (key_value.first == std::string("none")) { Resources::MenuIcons::NONE.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("rename")) { Resources::MenuIcons::RENAME.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("delete")) { Resources::MenuIcons::_DELETE.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("open_in_explorer")) { Resources::MenuIcons::OPEN_IN_EXPLORER.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
				}
				continue;
			}

			if (pe::__removeWiteSpace(line) == std::string("other_icons:")) {
				while (std::getline(init_file, line)) {
					if (pe::__removeWiteSpace(line) == std::string("end")) break;
					key_value = CLI::getKeyValue(line);
					if (key_value.first == std::string("warning")) { Resources::OtherIcons::WARNING.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("explorer_up")) { Resources::OtherIcons::EXPLORER_UP.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
					if (key_value.first == std::string("explorer_refresh")) { Resources::OtherIcons::EXPLORER_REFRESH.loadFromFile(CLI::getExecPath().append(key_value.second[0])); continue; }
				}
				continue;
			}


		}
	}
}