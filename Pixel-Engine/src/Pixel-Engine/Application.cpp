#include "pepch.h"

#include "Application.h"

#include "Logger.h"

namespace PE
{
	Application::Application() {}
	Application::~Application() {}

	void Application::run()
	{
		// temp code
		std::shared_ptr<Logger> sp = Logger::create();
		sp->log("testing");
		m_window = Window::create();
		m_window->Init();
		while (m_window->isOpen()) {
			
		}	
	}
}