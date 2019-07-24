#include "pepch.h"
#include "Application.h"

//testing include
#include "Input/Event.h"

namespace PE
{
	Application::Application() {
		m_window = Window::create();
		Logger::Init();
	}
	Application::~Application() {}

	void Application::run()
	{
		m_window->Init();

		sf::Clock clock;
		long last_time = clock.getElapsedTime().asMicroseconds();
		double dt=0;

		while (m_window->isOpen()) {
			dt += clock.restart().asMicroseconds() / 1000000.0;

			if (dt >= 1 / m_frame_rate) {
				
				// process(dt); input(d	t); ...
				dt -= (1 / m_frame_rate);
			}

			double interpolation = dt / (1 / m_frame_rate);
			// render(interpolation);

		}	
	}
}