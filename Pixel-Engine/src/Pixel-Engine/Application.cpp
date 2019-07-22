#include "pepch.h"
#include "Application.h"

namespace PE
{
	Application::Application() {}
	Application::~Application() {}

	void Application::run()
	{
		// temp code
		std::shared_ptr<Logger> sp = Logger::create();
		//sp->setLevel( Logger::Level::L_ERROR );
		sp->success("success");
		sp->info("an information is here and it this function will change");
		sp->warn("warning you shouldnt be doing that !!!");
		sp->error("something went wrong");
		sp->fatal("fatal error");
		// PE_ASSERT(false, __CLASS__)

		m_window = Window::create();
		m_window->Init();

		while (m_window->isOpen()) {
			
		}	
	}
}