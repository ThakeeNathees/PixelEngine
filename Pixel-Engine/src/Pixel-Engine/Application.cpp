#include "pepch.h"

#include "Application.h"

namespace PE
{
	Application::Application() {}
	Application::~Application() {}

	void Application::run()
	{
		// temp code
		m_window = Window::create();
		m_window->Init();
		while (m_window->isOpen()) {
		}	
	}
}