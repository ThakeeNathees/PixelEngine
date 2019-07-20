#pragma once

#include "Core.h"
#include "Pixel-Engine/Window.h"

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


