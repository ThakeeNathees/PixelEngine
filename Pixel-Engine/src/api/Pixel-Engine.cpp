#include "pch.h"
#include "Pixel-Engine.h"

#include "core.h"
char Logger::s_buf[4096];
std::string Logger::s_path = "./log.txt"; // default
std::ofstream Logger::s_outfile;

#include <pybind11/embed.h>
namespace py = pybind11;

#ifdef _WIN32
	#include <direct.h>
	#define getCurrentDir _getcwd
	#define changeDir _chdir
#else
	#include "unistd.h"
	#define getCurrentDir getcwd
	#define changeDir chdir
#endif

PIXEL_ENGINE_API void pe_mainLoop(const char* project_name, int argc, char** argv)
{

	std::ifstream init_file("init");
	if (init_file.is_open()) {
		std::string path;
		std::getline(init_file, path);
		changeDir(path.c_str());
		std::getline(init_file, path);
		Logger::init(path);
		init_file.close();
	}

	PE_LOG("engine initialized"); 
	char buf[4096];
	PE_LOG("cwd : %s", getCurrentDir(buf, sizeof buf));

	py::scoped_interpreter intp;
	PE_LOG("python interpriter initialized");

	pe::Application app(  std::string(project_name).append(".peproj.xml").c_str() );
	app.update();
}
