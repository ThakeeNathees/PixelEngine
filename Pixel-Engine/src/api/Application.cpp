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

	void Application::addScene( Scene* scene) {
		m_scenes[scene->getName()] = scene;
		scene->setSceneWindowSize({ m_window->getSize().x, m_window->getSize().y });
	}
	void Application::setCurrentScene(std::string scene_name) {
		assert( m_scenes.find(scene_name) != m_scenes.end() && "invalid scene name to set" );
		m_current_scene = m_scenes[scene_name];
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
			while (m_window->pollEvent(event)) {
				for (Object* object : m_current_scene->getObjects()) {
					if (object->input(event)) break;
				}
			}

			dt += clock.restart().asMicroseconds() / 1000000.0;
			if (dt >= 1 / m_frame_rate) {
				for (Object* object : m_current_scene->getObjects()) {
					object->process(dt);
				}
				dt -= (1 / m_frame_rate);
			}
			double interpolation = dt / (1 / m_frame_rate);

			m_window->clear(m_background_color);                     // TODO: ..., scene background, ...
			if ( m_current_scene->getBackground()->getVisible() )
				m_window->draw( m_current_scene->getBackground()->getBgSprite() );
			for (Object* object : m_current_scene->getObjects()) { 
				m_window->draw(*object->getSprite());
			}
			m_window->display();
		}
	}
}