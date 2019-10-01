#include "pch.h"

#include <pybind11/stl.h>
#include "pybind11/embed.h"
namespace py = pybind11;

#include "core/cli/CLI.h"
#include "windows/StartWindow.h"
#include "core/Resources.h"
#include "windows/FileTree.h"


int main(int argc, char** argv)
{

	py::scoped_interpreter intrp;
	py::exec("import sys, os");
	

	unsigned int w = sf::VideoMode::getDesktopMode().width - 600;
	unsigned int h = sf::VideoMode::getDesktopMode().height - 300;

	sf::RenderWindow window(sf::VideoMode(w, h), "Pixel-Engine");//, sf::Style::None);


	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	CLI::getInstance()->init();
	//CLI::chDir("C:/dev");

	window.setIcon( Resources::LOGO.getSize().x, Resources::LOGO.getSize().y, Resources::LOGO.copyToImage().getPixelsPtr());
	// process command lne arguments
	//CLI::parseArgs(argc, argv);


	StartWindow::getInstance()->dispStartWindow(window);


	sf::Event event; sf::Clock clock;
	while (window.isOpen()) {
		// event handle
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::GainedFocus) { FileTree::getInstance()->reload(); }
		}
		ImGui::SFML::Update(window, clock.restart());

		// render
		show_dock_space();
		FileTree::getInstance()->render();
		TextEditors::renderEditors();
		HexEditors::renderEditors();
		FontViwers::renderFontViwers();


		ImGui::ShowTestWindow();


		//window.clear();
		ImGui::SFML::Render(window);
		window.display();

	}
	ImGui::SFML::Shutdown();
	return 0;
}
