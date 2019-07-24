#include "pepch.h"
#include "Window.h"

namespace PE
{


	class RenderWindow : public Window
	{
	public:
		// constructor init distructor ...
		RenderWindow() {}
		RenderWindow(const Window::Prop& prop)
			:m_prop(prop){}
		

		void Init() override
		{
			PE_ASSERT(!s_is_window_created, "can't initialize window twice");
			if (s_is_window_created) {
				PE_ERROR("can't initialize window twice : remove extra Application::getWindow()->Init();");
				PE_ERROR_PAUSE();
			}
			s_is_window_created = true;
			m_window = new sf::RenderWindow(sf::VideoMode(m_prop.size.x, m_prop.size.y), m_prop.title);
			if ( m_prop.position.x > 0 && m_prop.position.y >0 )
				m_window->setPosition({ static_cast<int>(m_prop.position.x), static_cast<int>(m_prop.position.y) });
		}

		~RenderWindow()
		{
			delete m_window;
		}
		
		// getters 
		vect2 getSize() const override {
			PE_ASSERT(m_window != NULL, "initialize window before using it");
			if (m_window) return vect2( m_window->getSize().x, m_window->getSize().x );
		}
		vect2 getPosition() const override {
			PE_ASSERT(m_window != NULL, "initialize window before using it");
			if (m_window) return vect2( m_window->getPosition().x, m_window->getPosition().y );
		}
		std::string getTitle() const override {
			PE_ASSERT(m_window != NULL, "initialize window before using it");
			return m_prop.title;
		}

		bool isOpen() const override {
			PE_ASSERT( m_window != NULL , "initialize window before using it");
			return m_window->isOpen();
		}

		// setters 
		virtual void setPosition(const vect2& pos) override {
			PE_ASSERT(m_window != NULL, "initialize window before using it");
			m_window->setPosition(  sf::Vector2i(pos.x, pos.y) );
		}

	protected:
		sf::RenderWindow* m_window = nullptr;
		friend Input;
		Prop m_prop;

	}; // RenderWindow
	

	bool Window::s_is_window_created = false;

	std::shared_ptr<Window> Window::create(const Window::Prop& prop)
	{
		auto render_window =  std::make_shared<RenderWindow>(prop);
		// TODO: set the window as Input's static winow.
		return render_window;
	}

}


