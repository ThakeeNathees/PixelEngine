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
		for (auto obj : m_current_scene->getObjects()) {
			obj->init();
		}
	}

	void Application::update()
	{
		sf::Clock clock;
		long last_time = clock.getElapsedTime().asMicroseconds();
		double dt = 0;

		while (m_window->isOpen()) {
			sf::Event event;
			while (m_window->pollEvent(event)) {}

			dt += clock.restart().asMicroseconds() / 1000000.0;
			if (dt >= 1 / m_frame_rate) {
				for (Object* object : m_current_scene->getObjects()) {
					object->process(dt);
				}
				dt -= (1 / m_frame_rate);
			}
			double interpolation = dt / (1 / m_frame_rate);

			m_window->clear(m_background_color);                     // TODO: ..., scene background, ...
			for (Object* object : m_current_scene->getObjects()) { 
				m_window->draw(*object->getSprite());
			}
			m_window->display();
		}
	}
}