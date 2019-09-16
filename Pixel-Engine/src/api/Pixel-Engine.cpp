#include "pch.h"
#include "Pixel-Engine.h"

#include "core.h"
char Logger::s_buf[4096];
std::string Logger::s_path = "./log.txt"; // default
std::ofstream Logger::s_outfile;
bool Logger::s_is_init = false;

void pe_readInitFile();

#include <pybind11/embed.h>
namespace py = pybind11;

PIXEL_ENGINE_API void pe_mainLoop(const char* project_name, int argc, char** argv)
{
	pe_readInitFile();
	PE_LOG("engine initialized");

	char buf[4096];
	PE_LOG("cwd : %s", getCurrentDir(buf, sizeof buf));

	py::scoped_interpreter intp;
	PE_LOG("python interpriter initialized");
	py::exec("import sys");
	for (auto& path : pe::Assets::getPyobjectPaths()) {

		py::exec(std::string("sys.path.append('").append(path).append("')"));
	}

	pe::Application app(  std::string(project_name).append(".peproj").c_str() );
	app.update();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pe_readInitFile() {
	std::ifstream init_file("init");
	if (init_file.is_open()) {
		std::string line;
		while (std::getline(init_file, line)) {
			auto dict = pe::split(line, '=');
			if (dict.size() >= 2) {
				std::string key = pe::__removeWiteSpace(dict[0]);
				std::string value = pe::__getValueString(dict[1]);
				if (key == std::string("conf")) {
					if (value == std::string("debug")) { pe::Application::s_conf = 0; continue; }
					if (value == std::string("release")) { pe::Application::s_conf = 1; continue; }
					PE_CONSOLE_LOG("ERROR: unknown config value in init file!\ndefault config=release");
					continue;
				}
				if (key == std::string("cwd")) { changeDir(value.c_str()); continue; }
				if (key == std::string("log")) { Logger::init(value.c_str()); continue; }
				if (key == std::string("kill_switch")) {
					PE_CONSOLE_LOG("kill_switch = \"%s\"", value);
					auto key = pe::__getFunctionKey(value);
					pe::Application::s_kill_switch = key;
				}
			}
		}
	}
	if (!Logger::s_is_init) Logger::init(Logger::s_path);
}
