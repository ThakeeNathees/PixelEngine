#include "pepch.h"


#include <SFML/Graphics.hpp>
#include "Window.h"

namespace PE
{


	class RenderWindow : public Window
	{
	public:
		RenderWindow() {}
		RenderWindow(const Window::Prop& prop)
			:m_prop(prop){}
		

		void Init() override
		{
			m_window = new sf::RenderWindow(sf::VideoMode(m_prop.size.x, m_prop.size.y), m_prop.title);
			if ( m_prop.position.x > 0 && m_prop.position.y >0 )
				m_window->setPosition({ static_cast<int>(m_prop.position.x), static_cast<int>(m_prop.position.y) });
		}

		~RenderWindow()
		{
			delete m_window;
		}
		
		/* getters  */
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

		/*  setters  */

	protected:
		sf::RenderWindow* m_window = nullptr;
		Prop m_prop;

	};
	
	
	std::shared_ptr<Window> Window::create(const Window::Prop& prop)
	{
		return  std::make_shared<RenderWindow>(prop);
	}

}


