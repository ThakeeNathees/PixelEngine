#pragma once
#include "core.h"

#include "Scene.h"
#include "Assets.h"

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
		inline void setDebugMode(bool is_debug_mode) { m_is_debug_mode = is_debug_mode; }
		inline void setBgColor(const sf::Color& color) { m_background_color = color; }

		// getters
		inline sf::RenderWindow& getWindow() const { assert(m_window != nullptr); return *m_window; }
		inline Scene& getCurrentScene() const { assert(m_current_scene != nullptr); return *m_current_scene; }
		inline bool isDebugMode() { return m_is_debug_mode; }

		inline bool hasWindow() const { return m_window != nullptr; }
		inline bool hasScene() const { return m_current_scene != nullptr; }

	private:
		double m_frame_rate = 30.0;
		sf::Color m_background_color = sf::Color(80, 80, 80, 255);
		sf::RenderWindow* m_window = nullptr;
		std::map<std::string, Scene*> m_scenes;
		Scene* m_current_scene = nullptr;
		bool m_is_debug_mode = false;
	};
}
