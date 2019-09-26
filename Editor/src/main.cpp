#include "pch.h"

#include <pybind11/stl.h>
#include "pybind11/embed.h"
namespace py = pybind11;

#include "core/cli/CLI.h"
#include "core/Resources.h"
#include "windows/FileTree.h"
#include "windows/Explorer.h"

#include "windows/Popups.h"

// forward declaration
void show_dock_space();

void startWindow(sf::RenderWindow&);

int main(int argc, char** argv)
{

	py::scoped_interpreter intrp;
	py::exec("import sys, os");
	

	unsigned int w = sf::VideoMode::getDesktopMode().width - 600;
	unsigned int h = sf::VideoMode::getDesktopMode().height - 300;

	sf::RenderWindow window(sf::VideoMode(w, h), "Pixel-Engine");//, sf::Style::None);
	//sf::Texture icon_tex; icon_tex.loadFromFile("res/logo/logo.png");
	//window.setIcon(icon_tex.getSize().x, icon_tex.getSize().y, icon_tex.copyToImage().getPixelsPtr());


	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	CLI::getInstance()->init();
	CLI::chDir("C:/dev");

	// process command lne arguments
	//CLI::parseArgs(argc, argv);
	startWindow(window);


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

		Popups::render();

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
/////////////////////////////////////////////////////

void startWindow(sf::RenderWindow& window)
{
	ExplorerPopup explorer(".");
	sf::Event event; sf::Clock clock;
	while (window.isOpen()) {
		// event handle
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::GainedFocus) { FileTree::getInstance()->reload(); }
		}
		ImGui::SFML::Update(window, clock.restart());
		show_dock_space();
		
		//ImGui::ShowTestWindow();
		ImGui::Begin("Start");
		ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

		static char proj_name[1024];
		ImGui::InputText("proj_name", proj_name, sizeof(proj_name));

		static char proj_path[1024];
		ImGui::InputText("proj_path", proj_path, sizeof(proj_path));
		ImGui::SameLine();
		if (ImGui::ImageButton(Resources::OtherIcons::EXPLORER_UP)) {
			ImGui::OpenPopup("Explorer");
		}

		if (ImGui::Button("Create A New Project")) {
			if (proj_name[0] == '\0') ImGui::OpenPopup("Error!");
			else {
				CLI::getInstance()->projInit(explorer.getSelectedPath(), proj_name);
				ImGui::End();
				ImGui::SFML::Render(window);
				CLI::chDir( std::string(proj_path).append("/").append(proj_name) );
				return;
			}
		}

		if (ImGui::BeginPopupModal("Error!")) {
			ImGui::Text("Error! enter a Project Name!");
			if (ImGui::Button("OK")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		

		explorer.render();

		if (explorer.isPathSelected()) {
			const char* c = explorer.getSelectedPath().c_str();
			int i = 0;
			while (c[i]) {
				proj_path[i] = c[i++];
			}
		}
		ImGui::End();


		ImGui::SFML::Render(window);
		window.display();

	}
}