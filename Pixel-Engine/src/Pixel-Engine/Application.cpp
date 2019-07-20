#include <pepch.h>

#include "Application.h"

// test
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

namespace PE
{
	Application::Application()
	{
		// initialize window
	}
	Application::~Application() {}

	void Application::run()
	{
		sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Hello Cruel World");
		while (true) {
			//window.update()
		}
	}
}