#pragma once
#include "core.h"

#include "Scene.h"
#include "Assets.h"

namespace pe {

	struct PIXEL_ENGINE_API _peproj {
		inline _peproj(bool is_default=true) {
			if (is_default) assets_paths.push_back("assets.xml");
		}
		glm::ivec2 window_size = glm::ivec2(640, 480);
		std::string title = "Pixel-Engine";
		int frame_rate = 30;
		int begin_scene_id = static_cast<int>(Asset::Type::Scene);
		bool is_debug_mode = true;
		std::vector<std::string> assets_paths;
		sf::Color default_bg_color = sf::Color(80, 80, 80, 255);
	};

	class PIXEL_ENGINE_API Application
	{
	public:

		Application(const glm::ivec2& window_size, const std::string& title );
		Application(const struct _peproj& proj);
		Application(const Application& other) = delete;
		~Application();

		void update();

		// setters
		void addScene(Scene* scene);
		void addPersistenceObject(Object* obj);
		void setCurrentScene(int id);
		void setCurrentScene(const std::string& scene_name);
		inline void setDebugMode(bool is_debug_mode) { m_is_debug_mode = is_debug_mode; }
		inline void setBgColor(const sf::Color& color) { s_background_color = color; }
		inline void setFrameRate(int rate) { m_frame_rate = rate; }

		// getters
		inline sf::RenderWindow& getWindow() const { assert(m_window != nullptr); return *m_window; }
		inline Scene& getCurrentScene() const { assert(m_current_scene != nullptr); return *m_current_scene; }
		inline bool isDebugMode() { return m_is_debug_mode; }
		inline bool isDebugDrawArea() { return m_is_debug_draw_area; }

		inline bool hasWindow() const { return m_window != nullptr; }
		inline bool hasScene() const { return m_current_scene != nullptr; }

	private:

		void setCurrentScene(Scene* scene);
		double m_frame_rate = 30.0;
		bool m_is_debug_mode = true;
		bool m_is_debug_draw_area = true;

		Signal m_scene_changed_signal;
		Scene* m_current_scene = nullptr;
		sf::RenderWindow* m_window = nullptr;
		std::vector<Object*> m_persistent_objects;
		std::vector<Scene*> m_scenes;

		static sf::Color s_background_color;
	};
}
