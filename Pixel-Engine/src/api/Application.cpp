#include "pch.h"
#include "Application.h"

#include "entities/Sprite.h"

// testing
#include "..//utils/XmlFile.h"

namespace pe
{
	Application::Application()
	{
		m_window = new sf::RenderWindow(sf::VideoMode(640,480), "pixel-engine");
	}
	Application::~Application() {}

	void Application::update()
	{
		/*Sprite sp;
		sp.loadTexture("res/sheet.png");
		sp.setFrames(12, 8);
		sp.setFrameIndex(0);*/
		while (m_window->isOpen()) {
			sf::Event event;
			while (m_window->pollEvent(event)) {}


			m_window->clear({50, 75, 100, 255});
			//m_window->draw(sp);
			m_window->display();
		}
	}
}