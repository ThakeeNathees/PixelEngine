#pragma once
#include "core.h"

#include "Scene.h"

namespace pe {

	class PIXEL_ENGINE_API Application
	{
	public:
		Application();
		~Application();

		void addScene( std::string scene_name, Scene* scene);
		void setCurrentScene(std::string scene_name); // assert here

		void update();

	private:
		double m_frame_rate = 30.0;
		sf::Color m_background_color = sf::Color(80, 80, 80, 255);
		sf::RenderWindow* m_window;
		std::map<std::string, Scene*> m_scenes;
		Scene* m_current_scene;
	};
}
