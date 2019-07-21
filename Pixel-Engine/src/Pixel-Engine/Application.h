#pragma once

#include "Window.h"
#include "Core.h"

namespace PE
{
	class PIXEL_ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();	
		void run();

	private:
		std::unique_ptr<Window> m_window;
	};

	// To be defined in CLIENT
	Application* createApplication();
}


