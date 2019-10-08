#pragma once
#include "core.h"
#include "Assets.h"

namespace pe {

	struct PIXEL_ENGINE_API _peproj {
		sf::Vector2i window_size = sf::Vector2i(640, 480);
		std::string title = "Pixel-Engine-Project";
		int frame_rate = 30;
		int begin_scene_id = static_cast<int>(Asset::Type::Scene);
		bool is_debug_mode = true;
		bool no_console_window = false;
		int logo_texture_id = -1;
		sf::Color default_bg_color = sf::Color(80, 80, 80, 255);
		std::string assets_path = "assets.xml";
		std::vector<std::string> objects_path;
		std::vector<std::string> pypaths;
		std::vector<std::string> scene_paths;

	};

	class PIXEL_ENGINE_API Application
	{
	public:
		Application(const char* proj_path, bool create_window = true, sf::RenderTarget* render_target = nullptr); // if create_window == false render target
		Application(const Application& other) = delete;
		~Application();

		// these parameters are for multhread of the editor window -> use as application.update(); without any args
		void update();

		// never use this
		void __process(double* dt);
		void __handleEvent(pe::Event* event);

		// setters
		void addScene(Scene* scene);
		void addPersistenceObject(Object* obj);
		void setCurrentScene(int id);
		void setCurrentScene(const std::string& scene_name);
		inline void setDebugMode(bool is_debug_mode) { m_is_debug_mode = is_debug_mode; }
		inline void setBgColor(const sf::Color& color) { s_background_color = color; }
		inline void setFrameRate(int rate) { m_frame_rate = rate; }

		void reloadScritps() {
			try {
				for (auto obj : m_current_scene->getObjects()) obj->scriptReload();
			}
			catch (const std::exception& e){
				PE_LOG("\nERROR: in pe::Application::reloadScripts :\n%s", e.what() );
				PE_CONSOLE_LOG("\nERROR: in pe::Application::reloadScripts :\n%s", e.what() );
				if (m_window == nullptr) throw e; // throw to editor
			}
		}

		// getters
		inline sf::RenderWindow& getWindow() const { assert(m_window != nullptr); return *m_window; }
		inline Scene& getCurrentScene() const { 
			if (m_current_scene == nullptr) {
				if (m_window == nullptr) throw std::exception("Error : in pe::Application::getCurrentScene() -> m_curent_scene was nullptr");
				else assert(m_current_scene != nullptr); 
			}
			return *m_current_scene; 
		}
		inline bool isDebugMode()  const { return m_is_debug_mode; }
		inline bool isDebugDrawArea() const { return m_is_debug_draw_area; }
		inline double getCurrentFrameRate() const { return m_current_frame_rate; }

		inline bool hasWindow() const { return m_window != nullptr; }
		inline bool hasScene() const { return m_current_scene != nullptr; }

		inline static const sf::Vector2i& getWindowSize() { return s_window_size; }

		static sf::Color s_default_color;
		static sf::Keyboard::Key s_kill_switch;
	private:
		struct _peproj m_peproj;
		bool isEventKillSwitch(sf::Event& event);

		void setCurrentScene(Scene* scene);
		bool m_running = true;
		double m_frame_rate = 30.0;
		bool m_is_debug_mode = true;
		bool m_is_debug_draw_area = true;

		Signal m_scene_changed_signal = Signal("scene_changed", Signal::Type::SCENE_CHANGE);
		Scene* m_current_scene = nullptr;
		sf::RenderWindow* m_window = nullptr;
		sf::RenderTarget* m_render_target = nullptr;
		pe::Event m_event;
		sf::Clock m_clock;
		std::vector<Object*> m_persistent_objects;
		std::vector<Scene*> m_scenes;

		// actual frame rate = 1/dt
		double m_current_frame_rate = 0;

		static sf::Vector2i s_window_size;
		static sf::Color s_background_color;

	};
}
