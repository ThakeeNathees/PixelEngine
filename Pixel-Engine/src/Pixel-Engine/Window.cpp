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
			s_window = new sf::RenderWindow(sf::VideoMode(m_prop.size.x, m_prop.size.y), m_prop.title);
			if ( m_prop.position.x > 0 && m_prop.position.y >0 )
				s_window->setPosition({ static_cast<int>(m_prop.position.x), static_cast<int>(m_prop.position.y) });
		}

		~RenderWindow()
		{
			delete s_window;
		}
		
		// getters 
		vect2 getSize() const override {
			PE_ASSERT(s_window != NULL, "initialize window before using it");
			if (s_window) return vect2(s_window->getSize().x, s_window->getSize().x );
		}
		vect2 getPosition() const override {
			PE_ASSERT(s_window != NULL, "initialize window before using it");
			if (s_window) return vect2(s_window->getPosition().x, s_window->getPosition().y );
		}
		std::string getTitle() const override {
			PE_ASSERT(s_window != NULL, "initialize window before using it");
			return m_prop.title;
		}

		bool isOpen() const override {
			PE_ASSERT(s_window != NULL , "initialize window before using it");
			return s_window->isOpen();
		}

		// pollEvent
		virtual bool pollEvent(Event& event) {
			static sf::Event sfml_event;
			bool ret = s_window->pollEvent(sfml_event);


		}

		// setters 
		virtual void setPosition(const vect2& pos) override {
			PE_ASSERT(s_window != NULL, "initialize window before using it");
			s_window->setPosition(  sf::Vector2i(pos.x, pos.y) );
		}

	protected:
		static sf::RenderWindow* s_window;
		friend Input;
		Prop m_prop;


	}; // RenderWindow /////////////////////////////////////////////////////
	


	// RenderWindow implimentations
	sf::RenderWindow* RenderWindow::s_window = nullptr;
	bool Window::s_is_window_created = false;

	std::shared_ptr<Window> Window::create(const Window::Prop& prop)
	{
		return std::make_shared<RenderWindow>(prop);
	}

	// Input's implimentations
	vect2 Input::getMousePosition(bool relative_to_window)
	{
		if (relative_to_window) {
			auto position = sf::Mouse::getPosition(*(RenderWindow::s_window));
			return vect2(position.x, position.y);
		}
		auto position = sf::Mouse::getPosition();
		return vect2(position.x, position.y);	
	}


	void Input::setMousePosition(vect2 position, bool relative_to_window)
	{
		if (relative_to_window)
			sf::Mouse::setPosition( sf::Vector2i(position.x, position.y), *(RenderWindow::s_window) );
		sf::Mouse::setPosition( sf::Vector2i(position.x, position.y));
		
		
	}
}


