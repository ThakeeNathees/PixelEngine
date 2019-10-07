#include "pch.h"

#include "core/cli/CLI.h"
#include "windows/StartWindow.h"

#include "core/Resources.h"
#include "core/ApplicationHolder.h"

#include "core/MainMenuBar.h"
MainMenuBar* MainMenuBar::s_instance = nullptr;

#include "windows/PyInterpriter.h"
#include "core/Console.h"
/*
PYBIND11_EMBEDDED_MODULE(console, m) {
	py::class_<Console>(m, "Console")
		.def("addLog", [](Console& cons, const std::string& msg, int level = 0) {cons.addLog(msg, level); })
		;
}
*/

PYBIND11_EMBEDDED_MODULE(peio, m) {
	m
		.def("print", []() { CLI::getInstance()->getConsole()-> addLog( "" , 0); })
		.def("print", [](const py::object& msg) { CLI::getInstance()->getConsole()->addLog( py::str(msg).cast<std::string>(), 0); })
		.def("getMousePosition", []( bool relative) {
			if (relative) return ApplicationHolder::getMousePosition();
			else return ApplicationHolder::getMouseRelPosition();
			}, py::arg("relative")=true)
		.def("isWindowFocus", []() { return ApplicationHolder::isWindowFocus(); })
		;
	
}



#include "windows/FileTree.h"

#include "windows/assets_create/ObjectCreator.h"
#include "windows/assets_create/ScriptsCreator.h"


/* ****************** end of includes  *****************  */

int main(int argc, char** argv)
{

	py::scoped_interpreter intrp;
	py::exec("import sys, os");
	py::exec("import pixel_engine as pe");

	// create window
	unsigned int w = sf::VideoMode::getDesktopMode().width - 600;
	unsigned int h = sf::VideoMode::getDesktopMode().height - 300;
	sf::RenderWindow window(sf::VideoMode(w, h), "Pixel-Engine");//, sf::Style::None);


	// initialize
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	CLI::getInstance()->init();
	Logger::init(CLI::getExecPath().append("/log.txt")  );
	PE_LOG("Pixel-Engine initialized");
	window.setIcon( Resources::LOGO.getSize().x, Resources::LOGO.getSize().y, Resources::LOGO.copyToImage().getPixelsPtr());
	StartWindow::getInstance()->init();
	WindowManager::init();

	// start window render loop
	PE_LOG("start window loop started");
	StartWindow::getInstance()->dispStartWindow(window);
	PE_LOG("start window loop ended");

	// Load applicaton's assets
	int error = Resources::readProjFile();


	/**********************     MAIN LOOP     **********************/
	sf::Clock clock;
	pe::Event event; 
	double dt =0;

	while (window.isOpen()) {
		// event handle
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::GainedFocus) { FileTree::getInstance()->reload(); }
			
			// event handle for applicaton
			if (ApplicationHolder::isRunning()) {
				try {
					ApplicationHolder::getApplication()->__handleEvent(&event);
				}
				catch (const std::exception& e){
					if (!ApplicationHolder::hasError()) {
						CLI::getInstance()->getConsole()->addLog(e.what(),3);
						ApplicationHolder::setError(true);
					}
				}
			}
		} // end of event handle

		/* ***********************	process and render ********************** */
		ImGui::SFML::Update(window, clock.restart());

		// process application
		if (ApplicationHolder::isRunning()){
			try {
				ApplicationHolder::getApplication()->__process(&dt);
			}
			catch (const std::exception& e){
				if (!ApplicationHolder::hasError()) {
					ApplicationHolder::setError(true);
					CLI::getInstance()->getConsole()->addLog(e.what(), 3);
				}
			}
		}

		// render windows
		show_dock_space();
		MainMenuBar::getInstance()->render();

		FileTree::getInstance()->render();
		CLI::getInstance()->getConsole()->render();
		PyInterpriter::getInstance()->render();

		TextEditors::renderEditors();
		HexEditors::renderEditors();
		FontViwers::renderFontViwers();

		ObjectCreater::getInstance()->render();
		ScriptCreator::getInstance()->render();
		
		ApplicationHolder::render();

		ImGui::ShowTestWindow();

		ImGui::SFML::Render(window);
		window.display();

	}

	/***************************************************************/

	ImGui::SFML::Shutdown();
	return 0;
}
