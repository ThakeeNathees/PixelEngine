#pragma once
#include "core.h"
#include "Assets.h"


namespace pe {

	struct PIXEL_ENGINE_API _peproj {
		glm::ivec2 window_size = glm::ivec2(640, 480);
		std::string title = "Pixel-Engine-Project";
		int frame_rate = 30;
		int begin_scene_id = static_cast<int>(Asset::Type::Scene);
		bool is_debug_mode = true;
		bool no_console_window = false;
		std::vector<std::string> assets_paths;
		int window_icon_texture_id = -1;
		sf::Color default_bg_color = sf::Color(80, 80, 80, 255);
	};

	class PIXEL_ENGINE_API Application
	{
	public:
		static void test(Application& app);

		Application(const sf::Vector2i& window_size, const std::string& title );
		Application(const struct _peproj& proj);
		Application(const Application& other) = delete;
		~Application();

		static void mainLoop(const _peproj& proj); // scope of python interpriter

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

		static sf::Color s_default_color;
	private:

		struct _peproj m_peproj;

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
