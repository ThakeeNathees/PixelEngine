#include "pch.h"


#include "core/CLI.h"
#include "windows/StartWindow.h"

#include "core/Resources.h"
#include "core/EmbededApplication.h"

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
		.def("getMousePosition", []() {
				return EmbededApplication::getInstance()->getMousePosition();
			})
		.def("isWindowFocus", []() { return EmbededApplication::getInstance()->isWindowFocus(); })
		;
	
}


#include "node_graph/node_graph.h"

#include "windows/file_tree/FileTree.h"

#include "windows/assets_create/ObjectCreator.h"
#include "windows/assets_create/ScriptsCreator.h"

#include "windows/projerty_editor/ObjPropEditor.h"
#include "windows/projerty_editor/SpritePropEditor.h"
#include "windows/projerty_editor/AreaPropEditor.h"
#include "windows/projerty_editor/ScenePropEditor.h"



/* ****************** end of includes  *****************  */
int main(int argc, char** argv)
{

	py::scoped_interpreter intrp;
	py::exec("import sys, os");
	py::exec("import pixel_engine as pe");
	py::exec("import peio");

	// create window
	unsigned int w = sf::VideoMode::getDesktopMode().width - 600;
	unsigned int h = sf::VideoMode::getDesktopMode().height - 300;
	sf::RenderWindow window(sf::VideoMode(w, h), "Pixel-Engine");

	// initialize
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	CLI::getInstance()->init();
	Logger::init(CLI::getExecPath().append("/log.txt") );
	PE_LOG("Pixel-Engine initialized"); CLI::log("Engine Initialized", Console::LOGLEVEL_SUCCESS);
	window.setIcon( Resources::LOGO.getSize().x, Resources::LOGO.getSize().y, Resources::LOGO.copyToImage().getPixelsPtr());

	StartWindow::getInstance()->init();
	Resources::init(w, h);


	int error = 0;
	do {
		// start window render loop
		PE_LOG("start window loop started");
		StartWindow::getInstance()->dispStartWindow(window, error);
		PE_LOG("start window loop ended");

		FileTree::getInstance()->reload();

		// Load applicaton's assets
		error = CLI::getInstance()->readProjFile();
		if (error) { error = 2; continue; }
		error = Resources::readAssets();
		if (error) { error = 3; continue; }
	} while (error);

	FileTree::getInstance()->reload(); // to reload objects tags;

	/**********************     MAIN LOOP     **********************/
	sf::Clock clock;
	pe::Event event; 
	double dt =0;

	// TODO: make embeded game application to a new thread

	while (window.isOpen()) {

		/* ***************** Event Handle ********************** */
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			ImageViwer::getInstance()->handleEvent(event);
			FontViwer::getInstance()->handleEvent(event);
			ScenePropEditor::getInstance()->handleEvent(event);

			if (event.type == sf::Event::Closed) window.close();
			// gain focus
			if (event.type == sf::Event::GainedFocus) { 
				FileTree::getInstance()->reload();
			}
			
			// event handle for applicaton
			if (EmbededApplication::getInstance()->isRunning()) {
				try {
					EmbededApplication::getInstance()->getApplication()->__handleEvent(&event);
				}
				catch (const std::exception& e){
					if (!EmbededApplication::getInstance()->hasError()) {
						CLI::getInstance()->getConsole()->addLog(e.what(),3);
						EmbededApplication::getInstance()->setError(true);
					}
				}
			}
		} // end of event handle

		/* ***********************	process and render ********************** */
		ImGui::SFML::Update(window, clock.restart());

		// process application
		if (EmbededApplication::getInstance()->isRunning()){
			try {
				EmbededApplication::getInstance()->getApplication()->__process(&dt);
			}
			catch (const std::exception& e){
				if (!EmbededApplication::getInstance()->hasError()) {
					EmbededApplication::getInstance()->setError(true);
					CLI::getInstance()->getConsole()->addLog(e.what(), 3);
				}
			}
		}

		/* ****************** Render Windows ******************** */
		show_dock_space();
		MainMenuBar::getInstance()->render();

		FileTree::getInstance()->render();
		PyInterpriter::getInstance()->render();
		CLI::getInstance()->getConsole()->render();

		ImageViwer::getInstance()->render(); // TOOD: correct the following spellings : viewer, embedded, interpreter
		FontViwer::getInstance()->render();
		TextEditors::renderEditors();
		HexEditors::renderEditors();

		ObjectCreater::getInstance()->render();
		ScriptCreator::getInstance()->render();

		ObjPropEditor::getInstance()->render();
		SpritePropEditor::getInstance()->render();
		AreaPropEditor::getInstance()->render();
		ScenePropEditor::getInstance()->render();

		EmbededApplication::getInstance()->render();

		
		/* node editor
		*/
		static bool open = true; if (open)ShowExampleAppCustomNodeGraph(&open);

		ImGui::ShowTestWindow();

		ImGui::SFML::Render(window);
		window.display();

	}

	/***************************************************************/

	ImGui::SFML::Shutdown();
	return 0;
}
