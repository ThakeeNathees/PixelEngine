#pragma once
#include "..//core.h"


#include "Sprite.h"
#include "Area.h"
#include "Signal.h"


namespace pe
{
	// forward class declaration
	class Scene;
	class Application;


	class PIXEL_ENGINE_API Object : public sf::Transformable, public sf::Drawable
	{
	public:
		Object();
		Object(const Object& other) = delete;
		~Object();

		// virtual functions
		inline virtual void init() {};
		inline virtual void process(double dt) {};
		inline virtual bool input(sf::Event& event) { return false; } // return if event handled ?
		inline virtual void recieveSignal(const Signal& signal) {}
		virtual void draw() const;
	private:
		void draw(const sf::Drawable& drawable) const;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void drawDebug(sf::RenderTarget& target)const;
	public:

		// draw methods
		sf::RenderTarget& getRenderTarget() const;
		void drawSelf() const;
		void drawRectangle(float x, float y, float width, float height, sf::Color color = m_default_color) const;
		inline void drawRectangle( const glm::vec2& position, const glm::vec2& dimension, sf::Color color = m_default_color) const { drawRectangle( position.x, position.y, dimension.x, dimension.y, color ); }
		inline void drawRectangle( const sf::Vector2f& position, const sf::Vector2f& dimension, sf::Color color = m_default_color) const { drawRectangle(position.x, position.y, dimension.x, dimension.y, color); }
		inline void drawRectangle( const sf::FloatRect& rect, sf::Color color = m_default_color) const { drawRectangle( rect.top, rect.left, rect.width, rect.height, color ); }
		inline void drawRectangle( const sf::RectangleShape& shape ) { draw( shape ); }

		void drawLine( float x1, float y1, float x2, float y2, float thickness = 5, sf::Color color = m_default_color)const; // TODO:	
		inline void drawLine(const glm::fvec2& point1, glm::fvec2& point2, float thickness = 5, sf::Color color = m_default_color) const {
			drawLine( point1.x, point1.y, point2.x, point2.y, thickness, color );
		}
		inline void drawLine(const sf::Vector2f& point1, const sf::Vector2f& point2, float thickness = 5, sf::Color color = m_default_color) const {
			drawLine(point1.x, point1.y, point2.x, point2.y, thickness, color);
		}

		void drawCircle(float x, float y, float r, sf::Color color = m_default_color) const;
		inline void drawCircle(const glm::fvec2& position, float r, sf::Color color = m_default_color) const { drawCircle( position.x, position.y, r, color ); }
		inline void drawCircle(const sf::Vector2f& position, float r, sf::Color color = m_default_color) const { drawCircle( position.x, position.y, r, color ); }


		void emitSignal(Signal& signal) ;

		// setters
		void setPosition(float x, float y);
		inline void setPosition(const glm::fvec2& position) { setPosition(position.x, position.y); }
		inline void setPosition(const sf::Vector2f& position) { setPosition(position.x, position.y); }
		void setRotation(float angle);
		void setScale(float x, float y);
		inline void setScale(float scale) { setScale(scale, scale); }
		inline void setScale(const glm::fvec2& scale) { setScale(scale.x, scale.y); }
		inline void setScale(const sf::Vector2f& scale) { setScale(scale.x, scale.y); }
		void setOrigin(float x, float y);
		inline void setOrigin(const glm::fvec2& position) { setOrigin(position.x, position.y); }
		inline void setOrigin(const sf::Vector2f& position) { setOrigin(position.x, position.y); }

		void move(float x, float y);
		inline void move(const sf::Vector2f& vect) { move( vect.x, vect.y ); }
		inline void move(const glm::fvec2& vect) { move(vect.x, vect.y); }
		void rotate(float angle);
		void scale(float x, float y);
		inline void scale(float x) { scale( x, x); }
		inline void scale(const sf::Vector2f& vect) { scale(vect.x, vect.y); }
		inline void scale(const glm::fvec2& vect) { scale(vect.x, vect.y); }

		void setSprite( Sprite* sprite );
		void setZIndex(int z_index);
		void setArea( Area* area = nullptr );

		inline void setVisible(bool visible) { m_visible = visible; }
		inline void setName(const std::string& name) { m_name = name; }

		// getters
		inline Application& getApplication() const	{ assert( m_applicaton != nullptr); return *m_applicaton; }
		inline Scene& getScene() const				{ assert( m_scene != nullptr);		return *m_scene; }
		inline Area& getArea() const				{ assert( m_area != nullptr);		return *m_area; }
		inline Sprite& getSprite() const			{ assert( m_sprite != nullptr);		return *m_sprite; }
		inline int getZIndex() const				{ return m_z_index; }
		inline int getId() const					{ return m_id; }
		
		inline bool hasApplication() const { return m_applicaton != nullptr; }
		inline bool hasScene() const { return m_scene != nullptr; }
		inline bool hasArea() const { return m_area != nullptr; }
		inline bool hasSprite() const { return m_sprite != nullptr; }

		inline bool getVisible() const { return m_visible; }
		inline const std::string& getName() const { return m_name; }

	private:
		inline void setScene(Scene* scene) { m_scene = scene; }
		friend class Scene;
		friend class Application;
		static int s_object_count;
		static sf::RenderTarget* s_render_target; // const methods can edit static field

		std::string m_name;
		int m_id;
		int m_z_index = 0; // small val render first
		bool m_visible				= true;
		Scene* m_scene				= nullptr;
		Application* m_applicaton	= nullptr;
		Sprite* m_sprite			= nullptr;
		Area* m_area				= nullptr;

		// for debug printing
		static sf::Color m_default_color;
		sf::CircleShape* m_dbg_origin  = nullptr;
	};
}