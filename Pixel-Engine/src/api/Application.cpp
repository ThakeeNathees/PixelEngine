#include "pch.h"
#include "Application.h"

#include "entities/Sprite.h"
#include "entities/Object.h"

#include "utils/math_utils.h"
#include "misc/Event.h"

#include "utils/AssetsReader.h"


#include <pybind11/embed.h>
namespace py = pybind11;

class T { public: int x; };
PYBIND11_EMBEDDED_MODULE(p, m) {
	py::class_<T>(m, "T")
		.def_readwrite("x",&T::x);
	m.def("test", []() {std::cout << "test called" << std::endl; });
}

namespace pe
{
	void Application::test() {
		py::scoped_interpreter intp;

		auto p = py::module::import("p");
		p.attr("test")();
		__debugbreak();
	}

	sf::Color Application::s_background_color = sf::Color(80, 80, 80, 255);

	Application::Application( const glm::ivec2& window_size, const std::string& title )
		: m_scene_changed_signal( Signal("scene_changed") )
	{
		m_window = new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y), title);
	}
	Application::Application(const struct _peproj& proj)
		: m_scene_changed_signal(Signal("scene_changed"))
	{
		m_window = new sf::RenderWindow(sf::VideoMode(proj.window_size.x, proj.window_size.y), proj.title);
		setDebugMode(proj.is_debug_mode);
		setFrameRate( proj.frame_rate );

		AssetsReader reader;
		for (auto path : proj.assets_paths) {
			reader.loadFile( path.c_str());
			reader.readAssets(this);
		}

		setCurrentScene( proj.begin_scene_id );
		setBgColor( proj.default_bg_color );
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
		assert( scene != nullptr );
		m_scenes.push_back(scene);
		scene->setSceneWindowSize({ m_window->getSize().x, m_window->getSize().y });
		for (auto obj : m_persistent_objects) scene->addObject(obj);
	}

	void Application::setCurrentScene(Scene* scene) {
		m_current_scene = scene;
		m_current_scene->clear();

		for (Object* obj : m_persistent_objects) obj->m_scene = m_current_scene;

		m_scene_changed_signal.clear();
		for (Object* obj : m_current_scene->getObjects()) m_scene_changed_signal.addReciever(obj);
		m_scene_changed_signal.setData(m_current_scene->getId());
		m_current_scene->addSignal(&m_scene_changed_signal);
		
		for (auto obj : m_current_scene->getObjects()) {
			obj->m_applicaton = this;
			obj->init();
			for (Timer* timer : obj->m_timers) m_current_scene->addTimer(timer);
		}
	}
	void Application::setCurrentScene(int id) {
		for (auto scene : m_scenes) {
			if (scene->getId() == id) {
				setCurrentScene(scene);
				return;
			}
		} assert(false && "invalid scene id to set");
	}
	void Application::setCurrentScene(const std::string& name) {
		for (auto scene : m_scenes) {
			if (scene->getName() == name) {
				setCurrentScene(scene);
				return;
			} assert( false && "invalid scene name to set" );
		}
	}

	/// main loop
	void Application::update()
	{
		sf::Clock clock;
		sf::Int64 last_time = clock.getElapsedTime().asMicroseconds();
		double dt = 0;

		while (m_window->isOpen()) {

			Event event;
			while (m_window->pollEvent(event)) {
				assert( m_current_scene );
				for (Object* object : m_current_scene->getObjects()) {
					object->input(event);
					if (event.isHandled()) continue;
				}
			}
			// process
			dt += clock.getElapsedTime().asMicroseconds() / 1000000.0;
			if (dt >= 1 / m_frame_rate) {

				for (Timer* timer : m_current_scene->m_timers) {
					timer->update();
				}

				for (Signal* signal : m_current_scene->m_signals) {
					for (Object* object : signal->getRecievers()) {
						if (object != nullptr) object->recieveSignal(*signal);
					}
				}
				m_current_scene->m_signals.clear();

				for (Object* object : m_current_scene->getObjects()) {
					dt += clock.getElapsedTime().asMicroseconds() / 1000000.0;
					object->process(dt);
				}

				if (m_current_scene->getBackground()) { m_current_scene->getBackground()->move(dt); }
				dt -= (1 / m_frame_rate);
			}
			clock.restart();
			double interpolation = dt / (1 / m_frame_rate);

			// draw
			m_window->clear(s_background_color);
			if (m_current_scene->getBackground()){
				Background* bg = m_current_scene->getBackground();
				if (bg->isVisible()) m_window->draw( *bg );
			}

			for (pe::Drawable* drawable : m_current_scene->getDrawables()) {
				if (drawable->isVisible()) m_window->draw(*drawable);
			}
			m_window->display();
		}
	}
}