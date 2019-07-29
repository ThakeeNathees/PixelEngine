#include "pch.h"

#include <stdio.h>
#include "simpledir.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include "TextEditor.h"


void showDockSpace()
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
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	ImGui::PopStyleVar(3);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	ImGui::End();

}


long long whash(std::string str)
{
	long long ret=0;

	int i = 0;
	for (char c : str) {
		ret += c << (8*i++);
	}

	return ret;
}


void showTree(std::string path) {
	
	long long id = whash( SimpleDir::get_file_name(path) );
	static long long selected_id = -1;

	if (SimpleDir::isDirectory(path)) {
		if ( ImGui::TreeNode((path == ".") ? "files": SimpleDir::get_file_name(path).c_str() )) {
			SimpleDir dir;
			dir.open(path);
			for (std::string p : dir.getFiles()) {
				showTree(p);
			}
			ImGui::TreePop();
		}
	}
	else
	{
		ImGuiTreeNodeFlags node_flags=0;
		if (selected_id==id) node_flags |= ImGuiTreeNodeFlags_Selected;
		node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

		ImGui::PushStyleColor(0, {255,0,0,255});
		ImGui::TreeNodeEx((void*)(intptr_t)(id), node_flags, SimpleDir::get_file_name(path).c_str());
		ImGui::PopStyleColor();
		if (ImGui::IsItemClicked()) selected_id = id;
		
	}

}

void showTestWindow(std::string path)
{
	ImGui::Begin("file tree");
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	int id = 0;
	showTree(path);
	
	ImGui::End();
}



int main()
{
	// creating window and init
	unsigned int desktop_width = sf::VideoMode::getDesktopMode().width;
	unsigned int desktop_height = sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(desktop_width, desktop_height), "Pixel-Engine" );
	window.setPosition({0,0});
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	sf::Event event;
	sf::Clock clock;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) window.close();
		}
		ImGui::SFML::Update(window, clock.restart());

		showDockSpace();
		ImGui::ShowTestWindow();
		showTestWindow("c:/");


		window.clear();
		ImGui::SFML::Render(window);
		window.display();

	}
	ImGui::SFML::Shutdown();
	return 0;
}
