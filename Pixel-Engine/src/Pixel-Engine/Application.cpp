#include "Application.h"

#include <stdio.h>
#include <SFML/Window.hpp>

namespace PE
{
	Application::Application() {}
	Application::~Application() {}

	void Application::run()
	{
		sf::Window win(sf::VideoMode(640, 480), "Hello Cruel World");

		printf("teasdfadfrert        stf");
		while (true);
	}
}