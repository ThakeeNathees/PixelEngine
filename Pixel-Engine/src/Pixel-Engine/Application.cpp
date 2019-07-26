#include "pepch.h"
#include "Application.h"

//testing include
#include "Input/Event.h"

namespace pe
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

		// file util test
		std::ifstream file;
		file.open("test.test");
		if (file.fail()) PE_ERROR("cant open file");
		std::string line;
		while (std::getline(file, line)) {
			std::cout << line << std::endl;
		}

		while (m_window->isOpen()) {

			// event testing
			std::unique_ptr<Event>event(new Event());
			if (m_window->pollEvent(event)) {
				if (event->getType() == Event::MOUSE_WHEEL);
			}

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