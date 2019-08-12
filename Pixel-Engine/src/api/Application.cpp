#include "pch.h"
#include "Application.h"

#include "entities/Sprite.h"
#include "entities/Object.h"

// testing
#include "..//utils/XmlFile.h"

namespace pe
{
	Application::Application()
	{
		m_window = new sf::RenderWindow(sf::VideoMode(640,480), "pixel-engine");
		m_current_scene = nullptr;
	}
	Application::~Application() {
		for (auto scene : m_scenes) {
			delete scene.second;
		}
	}

	void Application::addScene(std::string scene_name, Scene* scene) {
		m_scenes[scene_name] = scene;
	}
	void Application::setCurrentScene(std::string scene_name) { 
		m_current_scene = m_scenes[scene_name];  // assert here
	}

	void Application::update()
	{
		while (m_window->isOpen()) {
			sf::Event event;
			while (m_window->pollEvent(event)) {}

			m_window->clear({50, 75, 100, 255});
			for (Object* object : m_current_scene->getObjects()) { // TODO: change draw order and more stuff
				m_window->draw(*object->getSprite());
			}
			m_window->display();
		}
	}
}