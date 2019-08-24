#include "pch.h"
#include "Application.h"

#include "entities/Sprite.h"
#include "entities/Object.h"

#include "..//utils/math_utils.h"

//#include "..//utils/XmlFile.h"

namespace pe
{
	Application::Application()
	{
		m_window = new sf::RenderWindow(sf::VideoMode(640, 480), "pixel-engine");
		m_current_scene = nullptr;
	}
	Application::~Application() {
		for (auto scene : m_scenes) {
			delete scene.second;
		}
	}

	void Application::addScene(Scene* scene) {
		m_scenes[scene->getName()] = scene;
		scene->setSceneWindowSize({ m_window->getSize().x, m_window->getSize().y });
	}
	void Application::setCurrentScene(std::string scene_name) {
		assert(m_scenes.find(scene_name) != m_scenes.end() && "invalid scene name to set");
		m_current_scene = m_scenes[scene_name];
		m_current_scene->clear();
		for (auto obj : m_current_scene->getObjects()) {
			obj->m_applicaton = this;
			obj->init();
			for (Timer* timer : obj->m_timers) m_current_scene->addTimer(timer);
		}
	}

	/// main loop
	void Application::update()
	{
		sf::Clock clock;
		sf::Int64 last_time = clock.getElapsedTime().asMicroseconds();
		double dt = 0;

		while (m_window->isOpen()) {

			sf::Event event;
			while (m_window->pollEvent(event)) {
				for (Object* object : m_current_scene->getObjects()) {
					m_event_handled = true;
					object->input(event);
					if (m_event_handled) { m_event_handled = false; continue; }
				}
			}
			// process
			dt += clock.getElapsedTime().asMicroseconds() / 1000000.0;
			if (dt >= 1 / m_frame_rate) {
				for (Object* object : m_current_scene->getObjects()) {
					dt += clock.getElapsedTime().asMicroseconds() / 1000000.0;
					object->process(dt);
				}

				for (Timer* timer : m_current_scene->m_timers) {
					timer->update();
				}

				for (Signal* signal : m_current_scene->m_signals) {
					for (Object* object : signal->getRecievers()) {
						if (object != nullptr) object->recieveSignal(*signal);
					}
				} m_current_scene->m_signals.clear();
				dt -= (1 / m_frame_rate);
			}
			clock.restart();
			double interpolation = dt / (1 / m_frame_rate);

			// draw
			m_window->clear(m_background_color);
			if (m_current_scene->hasBackground())
				m_window->draw(m_current_scene->getBackground());

			for (Object* object : m_current_scene->getObjects()) {
				if (object->getVisible()) m_window->draw(*object);
			}
			m_window->display();
		}
	}
}