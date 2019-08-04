#include "pch.h"

#include <stdio.h>
#include "simpledir.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include "TextEditor.h"

#include "windows/windows.h"

#define print(x) std::cout << x << std::endl;

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
			// event handle
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == 0) Console::addLog({Console::_WARNING, "[warning] you shouldn't be doing that"});
		}
		ImGui::SFML::Update(window, clock.restart());

		// layout
		show_dock_space();
		ImGui::ShowTestWindow();
		file_tree_window(".");
		EditorMap::renderEditors();
		Console::renderConsole();

		window.clear();
		ImGui::SFML::Render(window);
		window.display();

	}
	ImGui::SFML::Shutdown();
	return 0;
}
