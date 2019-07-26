#include "pepch.h"
#include "Application.h"
#include "Input/Event.h"

//testing include
#include "utils/File.h"

namespace pe
{
	Application::Application() {
		m_window = Window::create();
		Logger::Init();
	}
	Application::~Application() {}

	void Application::run()
	{
		// test code
		File file;
		int error = File::mkDir("res/folder");
		file.open(".");
		std::cout << file.toString() << std::endl;
			

		// initialize
		m_window->Init();
		sf::Clock clock;
		long last_time = clock.getElapsedTime().asMicroseconds();
		double dt=0;


		// main loop
		while (m_window->isOpen()) {

			// input event
			std::unique_ptr<Event>  event(new Event());
			if (m_window->pollEvent(event)) {
				if (event->getType() == Event::CLOSED)m_window->close();
			}

			dt += clock.restart().asMicroseconds() / 1000000.0;
			if (dt >= 1 / m_frame_rate) {	
				// process(dt)
				dt -= (1 / m_frame_rate);
			}
			double interpolation = dt / (1 / m_frame_rate);
			// render(interpolation);

		}	
	}
}