#pragma once
#include "Core.h"


namespace PE
{
	class PIXEL_ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void run();
	};

	// To be defined in CLIENT
	Application* createApplication();
}


