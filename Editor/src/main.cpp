#include "pch.h"

#include <stdio.h>
#include "simpledir.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Pixel-Engine.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "TextEditor.h"

#include "windows/window_manager.h"

#define print(x) std::cout << x << std::endl;

// TODO: add working dir
std::string working_dir = "C:/dev/__test_env/test_pe/";

int main()
{
	Globals::s_working_dir = std::string(working_dir);
	// creating window and initi and other inits //////////////////////
	unsigned int desktop_width = sf::VideoMode::getDesktopMode().width - 100;
	unsigned int desktop_height = sf::VideoMode::getDesktopMode().height - 100;
	sf::RenderWindow window(sf::VideoMode(desktop_width, desktop_height), "Pixel-Engine" );
	window.setPosition({0,0});
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	FileTree::init();
	RenderWindow::init();
	PropertyEditor::init();
	ImageViwer::init();
	AssetsWindow::init();

	// test
	pe::Assets::newAsset<pe::Texture>();
	pe::Assets::newAsset<pe::Texture>();
	
	pe::Sprite& sprite = *pe::Assets::newAsset<pe::Sprite>();
	pe::Texture& tex = *pe::Assets::newAsset<pe::Texture>();
	tex.loadFromFile( Globals::s_working_dir + std::string("res/sheet.png") );
	sprite.setTexture( tex);
	RenderWindow::test_sprite = &sprite;
	PropertyEditor::s_sprite = &sprite;
	////////////////////////////////////////////////////////////////

	sf::Event event;
	sf::Clock clock;
	while (window.isOpen()) {

		// event handle
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) window.close();

			ImageViwer::listenEvent(event);
			RenderWindow::listenEvent(event);
			// event handle Test
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == 0) Console::addLog({Console::_WARNING, "[warning] you shouldn't be doing that"});
		}
		ImGui::SFML::Update(window, clock.restart());

		// editor rendering
		WindowManager::show_dock_space();
		FileTree::renderFileTree(working_dir.c_str());
		WindowManager::windowSignalFromFileTree();
		EditorMap::renderEditors();
		Console::renderConsole();
		RenderWindow::renderRenderWindow();
		ImageViwer::renderImageViwer();
		PropertyEditor::renderPropertyEditor();
		AssetsWindow::renderAssetsWindow();


		ImGui::ShowTestWindow();

		window.clear();
		ImGui::SFML::Render(window);
		window.display();

	}
	ImGui::SFML::Shutdown();
	return 0;
}
