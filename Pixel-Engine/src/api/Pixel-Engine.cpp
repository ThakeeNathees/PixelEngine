#include "pch.h"
#include "Pixel-Engine.h"

#include <pybind11/embed.h>
namespace py = pybind11;


PIXEL_ENGINE_API void pe_mainLoop(const char* project_name)
{
	py::scoped_interpreter intp;

	pe::AssetsReader reader(std::string(project_name).append(".peproj.xml").c_str());
	reader._readPeproj();
	pe::Application app(reader._getPeproj());
	pe::FileHandler h;
	//h.writeProject( reader._getPeproj() ,"./");
	__debugbreak();
	// for testing
	/*
	pe::AssetsWriter w;
	w.addAssets();
	w.save("test.xml");
	pe::Application::test(app);
	*/

	app.update();
}
