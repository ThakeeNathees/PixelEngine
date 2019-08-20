#pragma once
#include "core.h"

#include "Scene.h"

namespace pe {

	class PIXEL_ENGINE_API Application
	{
	public:
		Application();
		Application(const Application& other) = delete;
		~Application();

		void update();

		// setters
		void addScene(Scene* scene);
		void setCurrentScene(std::string scene_name);
		inline void setEventHandled() { m_event_handled = true; }

		// getters
		inline sf::RenderWindow& getWindow() const { assert(m_window != nullptr); return *m_window; }
		inline Scene& getCurrentScene() const { assert(m_current_scene != nullptr); return *m_current_scene; }

		inline bool hasWindow() const { return m_window != nullptr; }
		inline bool hasScene() const { return m_current_scene != nullptr; }

	private:
		double m_frame_rate = 30.0;
		sf::Color m_background_color = sf::Color(80, 80, 80, 255);
		sf::RenderWindow* m_window = nullptr;
		std::map<std::string, Scene*> m_scenes;
		Scene* m_current_scene = nullptr;
		bool m_event_handled = false;
	};
}
