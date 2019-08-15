#pragma once
#include "core.h"

#include "Scene.h"

namespace pe {

	class PIXEL_ENGINE_API Application
	{
	public:
		Application();
		~Application();

		void update();
		
		void addScene( Scene* scene);
		void setCurrentScene(std::string scene_name);

		inline sf::RenderWindow* getWindow() const { return m_window; }

	private:
		double m_frame_rate = 30.0;
		sf::Color m_background_color = sf::Color(80, 80, 80, 255);
		sf::RenderWindow* m_window;
		std::map<std::string, Scene*> m_scenes;
		Scene* m_current_scene;
	};
}
