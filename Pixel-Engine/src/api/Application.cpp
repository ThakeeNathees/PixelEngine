#include "pch.h"
#include "Application.h"

#include "entities/Sprite.h"
#include "entities/Object.h"

#include "utils/math_utils.h"
#include "misc/Event.h"


namespace pe
{
	Application::Application()
	{
		m_window = new sf::RenderWindow(sf::VideoMode(640, 480), "pixel-engine");
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

			Event event;
			while (m_window->pollEvent(event)) {
				for (Object* object : m_current_scene->getObjects()) {
					object->input(event);
					if (event.isHandled()) continue;
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
				}
				m_current_scene->m_signals.clear();
				if (m_current_scene->hasBackground()) { m_current_scene->getBackground().move(dt); }
				dt -= (1 / m_frame_rate);
			}
			clock.restart();
			double interpolation = dt / (1 / m_frame_rate);

			// draw
			m_window->clear(m_background_color);
			if (m_current_scene->hasBackground()){
				Background& bg = m_current_scene->getBackground();
				if (bg.getVisible()) m_window->draw( bg );
			}

			for (pe::Drawable* drawable : m_current_scene->getDrawables()) {
				if (drawable->getVisible()) m_window->draw(*drawable);
			}
			m_window->display();
		}
	}
}