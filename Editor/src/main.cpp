#include "pch.h"

#include <pybind11/stl.h>
#include "pybind11/embed.h"
namespace py = pybind11;

#include "cli/CLI.h"
#include <ostream>

// forward declaration
void show_dock_space();

int main(int argc, char** argv)
{

	TextEditor editor;
	TextEditor::LanguageDefinition language = TextEditor::LanguageDefinition::CPlusPlus();
	editor.SetLanguageDefinition(language);

	py::scoped_interpreter intrp;
	py::exec("import sys, os");

	CLI::init();


	// process command lne arguments
	CLI::parseArgs(argc, argv);
	

	unsigned int w = sf::VideoMode::getDesktopMode().width - 600;
	unsigned int h = sf::VideoMode::getDesktopMode().height - 300;

	sf::RenderWindow window(sf::VideoMode(w, h), "Pixel-Engine");//, sf::Style::None);
	//sf::Texture icon_tex; icon_tex.loadFromFile("res/logo/logo.png");
	//window.setIcon(icon_tex.getSize().x, icon_tex.getSize().y, icon_tex.copyToImage().getPixelsPtr());


	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;



	sf::Event event; sf::Clock clock;
	while (window.isOpen()) {
		// event handle
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) window.close();
		}
		ImGui::SFML::Update(window, clock.restart());

		// render editor
		show_dock_space();

		ImGui::Begin("demo_text_editor");
		editor.setFontScale(2);
		editor.Render("test");
		ImGui::End();

		ImGui::ShowTestWindow();


		//window.clear();
		ImGui::SFML::Render(window);
		window.display();

	}
	ImGui::SFML::Shutdown();
	return 0;
}
/////////////////////////////////////////

void show_dock_space()
{
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	bool p_open = false;
	ImGui::Begin("DockSpace", &p_open, window_flags);
	ImGui::PopStyleVar(3);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	ImGui::End();

}