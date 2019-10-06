#include "pch.h"
#include "Application.h"
#include "utils/FileHandler.h"

#include "entities/Sprite.h"
#include "entities/Object.h"

#include "utils/math_utils.h"
#include "misc/Event.h"


#include <pybind11/stl.h>
#include <pybind11/embed.h>
namespace py = pybind11;

#include "bindings/python/pybind.h"
#include "bindings/python/PythonObject.h"

namespace pe
{

	sf::Color Application::s_background_color = sf::Color(80, 80, 80, 255);
	sf::Color Application::s_default_color = sf::Color(50, 75, 100, 255);
	sf::Vector2i Application::s_window_size = sf::Vector2i(0,0);
	int Application::s_conf = 0;
	sf::Keyboard::Key Application::s_kill_switch = sf::Keyboard::Unknown;


	Application::Application(const char* proj_path, bool create_window, sf::RenderTarget* render_target)
	{
		setDebugMode( s_conf == 0 ); // TODO: make applicatin static class
		FileHandler file;
		int error = file.readProject(proj_path); // TODO: error handle
		if (error) { PE_LOG("project file reading error"); }
		else { PE_LOG("project file reading success"); }
		m_peproj = file.getProject();
		//setDebugMode(m_peproj.is_debug_mode);
		if (create_window) {
			m_window = new sf::RenderWindow(sf::VideoMode(m_peproj.window_size.x, m_peproj.window_size.y), m_peproj.title);
			m_render_target = m_window;
		}
		else {
			m_render_target = render_target;
		}
		s_window_size = sf::Vector2i(m_peproj.window_size.x, m_peproj.window_size.y);
		setFrameRate(m_peproj.frame_rate );
		if (m_window) m_window->setFramerateLimit(1/ m_peproj.frame_rate);
#ifdef _WIN32
		if ( !m_is_debug_mode ) FreeConsole();
		else PE_CONSOLE_LOG( "this console window only apear in debug mode" );
#endif

		for (auto& path : m_peproj.pypaths) {
			py::exec(std::string("sys.path.append('").append(path).append("')"));
		}
		// TODO: set assets.xml as the defaule assets path and don't change the name for consistency
		if (std::string(m_peproj.assets_path) != std::string("")) {
			error = file.readAssets(m_peproj.assets_path.c_str()); // TODO: error handle
			if (error) { PE_LOG("assets file reading error"); }
			else { PE_LOG("assets file reading success"); }
		}
		else; // TODO: create assets.xml file and add

		for (auto& path : m_peproj.objects_path) {
			PE_LOG("\nobject deserialization begin : %s", path.c_str());
			file.readObject(path.c_str(), this);
		}
		for (auto& path : m_peproj.scene_paths) {
			PE_LOG("\nscene deserialization begin : %s", path.c_str());
			file.readScenes(path.c_str(), this);
		}
		
		int texture_id = m_peproj.logo_texture_id;
		if (texture_id >= 0) {
			if (Assets::hasAsset(texture_id)) {
				auto tex = Assets::getAsset<Texture>(texture_id);
				if (m_window) m_window->setIcon(tex->getSize().x, tex->getSize().y, tex->copyToImage().getPixelsPtr());
			}
			else { PE_LOG("project logo not found in assets : texture id = %i", texture_id); }
		}
		setBgColor(m_peproj.default_bg_color );

		if (m_peproj.scene_paths.size() == 0) {
			PE_LOG("\nNo scene found using default scene!\n");
			auto scene = Assets::newAsset<Scene>();
			setCurrentScene(scene);
		}
		else setCurrentScene(m_peproj.begin_scene_id);

	}

	Application::~Application() {
		if ( m_window ) delete m_window;
	}

	void Application::addPersistenceObject(Object* obj) {
		for (auto _obj : m_persistent_objects) {
			if (_obj == obj) return;
		} m_persistent_objects.push_back(obj);
	}

	void Application::addScene(Scene* scene) {
		if (scene == nullptr){ PE_LOG("\nERROR: pe::Application::addScene(pe::Scene*) called with nullptr"); }
		assert( scene != nullptr );
		m_scenes.push_back(scene);
		for (auto obj : m_persistent_objects) scene->addObject(obj);
	}

	void Application::setCurrentScene(Scene* scene) {
		m_current_scene = scene;
		m_current_scene->clear();

		for (Object* obj : m_persistent_objects) obj->m_scene = m_current_scene;

		m_scene_changed_signal.clear();
		for (Object* obj : m_current_scene->getObjects()) m_scene_changed_signal.addReciever(obj);
		m_scene_changed_signal.scene_change_data.scene_id= m_current_scene->getId();
		m_scene_changed_signal.scene_change_data.scene_name = m_current_scene->getName().c_str();
		m_current_scene->addSignal(&m_scene_changed_signal);
		
		for (auto obj : m_current_scene->getObjects()) {
			obj->m_applicaton = this;
			obj->sceneEntered(m_current_scene);
			for (Timer* timer : obj->m_timers) m_current_scene->addTimer(timer);
		}
	}
	void Application::setCurrentScene(int id) {
		for (auto scene : m_scenes) {
			if (scene->getId() == id) {
				setCurrentScene(scene);
				return;
			}
		}
		PE_LOG("\nERROR: pe::Application::setCurrentScene(int) called with invalid id [%i]", id);
		assert(false && "invalid scene id to set");
	}
	void Application::setCurrentScene(const std::string& name) {
		for (auto scene : m_scenes) {
			if (scene->getName() == name) {
				setCurrentScene(scene);
				return;
			} 
		}
		PE_LOG("\nERROR: pe::Application::setCurrentScene(const std::string&) called with invalid name [%s]", name.c_str());
		assert( false && "invalid scene name to set" );
	}

	/// main loop
	void Application::update()
	{

		//sf::Int64 last_time = m_clock.getElapsedTime().asMicroseconds();
		double dt = 0;
		while (m_running) {
			if (m_window && !m_window->isOpen()) m_running = false;
			
			if (m_window) {
				while (m_window->pollEvent(m_event)) {
					if (isEventKillSwitch(m_event)) m_window->close();
					if (!m_current_scene) { PE_LOG("\nERROR: in pe::Application::update() current scene is NULL"); }
					assert(m_current_scene);
					for (Object* object : m_current_scene->getObjects()) {
						try { object->handleEvent(m_event); }
						catch (const std::exception & err) { PE_CONSOLE_LOG(err.what()); }
						if (m_event.isHandled()) continue;
					}
				}
			}
			// process

			dt += m_clock.getElapsedTime().asMicroseconds() / 1000000.0;
			if ( dt >= 1 / m_frame_rate) {
				m_current_frame_rate = 1 / dt;
				if (m_is_debug_mode && m_window) m_window->setTitle(m_peproj.title + std::string(" | DebugMode | fps : ").append(std::to_string(m_current_frame_rate)));
				for (Timer* timer : m_current_scene->m_timers) {
					timer->update();
				}

				for (Signal* signal : m_current_scene->m_signals) {
					for (Object* object : signal->getRecievers()) {
						if (object != nullptr) {
							try { object->recieveSignal(*signal); }
							catch (const std::exception & err) { PE_CONSOLE_LOG(err.what()); }
						}
					}
				}
				m_current_scene->m_signals.clear();

				for (Object* object : m_current_scene->getObjects()) {
					dt += m_clock.getElapsedTime().asMicroseconds() / 1000000.0;
					try { object->process(dt); }
					catch (const std::exception & err) { PE_CONSOLE_LOG(err.what()); }
				}

				if (m_current_scene->getBackground()) { m_current_scene->getBackground()->move(dt); }
				//dt -=  (1 / m_frame_rate);
				dt = 0;
			}
			m_clock.restart();
			double interpolation = dt / (1 / m_frame_rate);

			// draw
			m_render_target->clear(s_background_color);
			if (m_current_scene->getBackground()) {
				Background* bg = m_current_scene->getBackground();
				if (bg->isVisible()) m_render_target->draw(*bg);
			}

			for (pe::Drawable* drawable : m_current_scene->getDrawables()) {
				if (drawable->isVisible()) {
					try { m_render_target->draw(*drawable); }
					catch (const std::exception & err) { PE_CONSOLE_LOG(err.what()); }
				}
			}
			if (m_window) m_window->display();

			if (m_is_debug_mode && sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
				for (auto obj : m_current_scene->getObjects()) obj->scriptReload();
			}
		}
	}

	void Application::__process(double* dt) {
		// process
		*dt += m_clock.getElapsedTime().asMicroseconds() / 1000000.0;
		if (*dt >= 1 / m_frame_rate) {
			m_current_frame_rate = 1 / *dt;
			// reload
			if (m_is_debug_mode && sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
				for (auto obj : m_current_scene->getObjects()) obj->scriptReload();
			}

			for (Timer* timer : m_current_scene->m_timers) {
				timer->update();
			}

			for (Signal* signal : m_current_scene->m_signals) {
				for (Object* object : signal->getRecievers()) {
					if (object != nullptr) {
						try { object->recieveSignal(*signal); }
						catch (const std::exception & err) { throw err; }
					}
				}
			}
			m_current_scene->m_signals.clear();

			for (Object* object : m_current_scene->getObjects()) {
				*dt += m_clock.getElapsedTime().asMicroseconds() / 1000000.0;
				try { object->process(*dt); }
				catch (const std::exception & err) { throw err; }
			}

			if (m_current_scene->getBackground()) { m_current_scene->getBackground()->move(*dt); }
			*dt = 0;
		}
		m_clock.restart();
		double interpolation = *dt / (1 / m_frame_rate);

		// draw
		m_render_target->clear(s_background_color);
		if (m_current_scene->getBackground()) {
			Background* bg = m_current_scene->getBackground();
			if (bg->isVisible()) m_render_target->draw(*bg);
		}

		for (pe::Drawable* drawable : m_current_scene->getDrawables()) {
			if (drawable->isVisible()) {
				try { m_render_target->draw(*drawable); }
				catch (const std::exception & err) { throw err; }
			}
		}
		if (m_window) m_window->display();

		if (m_is_debug_mode && sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
			for (auto obj : m_current_scene->getObjects()) obj->scriptReload();
		}
	}

	void Application::__handleEvent(pe::Event* event) {
		if (isEventKillSwitch(*event)) m_window->close();
		if (!m_current_scene) { PE_LOG("\nERROR: in pe::Application::update() current scene is NULL"); }
		assert(m_current_scene);
		for (Object* object : m_current_scene->getObjects()) {
			try { object->handleEvent(*event); }
			catch (const std::exception & err) { throw err; }
			if (event->isHandled()) continue;

		}
	}

	// private functions ///////////////

	bool Application::isEventKillSwitch(sf::Event& event) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code != sf::Keyboard::Unknown && event.key.code == s_kill_switch) {
				return true;
			}
		}
		return false;
	}
}