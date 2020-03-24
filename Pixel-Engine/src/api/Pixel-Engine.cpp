#include "pch.h"
#include "Pixel-Engine.h"

#include "core.h"
char Logger::s_buf[4096];
std::string Logger::s_path = "./log.txt"; // default
std::ofstream Logger::s_outfile;
bool Logger::s_is_init = false;

void pe_readInitFile(std::string& proj_name);

#include <pybind11/embed.h>
namespace py = pybind11;

PIXEL_ENGINE_API void pe_mainLoop( int argc, char** argv)
{
	changeDir(pe::__getExecDir().c_str());
	char buf[4096];
	PE_CONSOLE_LOG("cwd : %s", getCurrentDir(buf, sizeof buf));

	std::string project_name;
	pe_readInitFile(project_name);

	PE_LOG("engine initialized");
	PE_LOG("cwd : %s", getCurrentDir(buf, sizeof buf));

	py::scoped_interpreter intp;
	PE_LOG("python interpriter initialized");
	py::exec("import sys");

	pe::Application app(  std::string(project_name).append(".peproj").c_str() );
	app.update();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pe_readInitFile(std::string& proj_name) {
	std::ifstream init_file("conf");
	if (init_file.is_open()) {
		std::string line;
		while (std::getline(init_file, line)) {
			auto dict = pe::split(line, '=');
			if (dict.size() >= 2) {
				std::string key = pe::__removeWiteSpace(dict[0]);
				std::string value = pe::__getValueString(dict[1]);
				if (key == std::string("cwd")) { 
					changeDir(value.c_str()); continue; 
				}
				if (key == std::string("log")) { Logger::init(value.c_str()); continue; }
				if (key == std::string("kill_switch")) {
					PE_CONSOLE_LOG("kill_switch = \"%s\"", value.c_str());
					auto key = pe::__getFunctionKey(value);
					pe::Application::s_kill_switch = key;
				}
				if (key == std::string("project")) {
					proj_name = value;
				}
			}
		}
	}
	else {
		if (!Logger::s_is_init) Logger::init(Logger::s_path);
		PE_CONSOLE_LOG("ERROR: conf.init not found.");
		PE_LOG("ERROR: conf.init not found.");
		exit(1);
	}
	if (!Logger::s_is_init) Logger::init(Logger::s_path);

}
