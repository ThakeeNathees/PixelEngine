#pragma once
#include "..//core.h"

#include "Sprite.h"
#include "Area.h"


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
		virtual void draw(sf::RenderTarget& target) const;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawDebug(sf::RenderTarget& target)const;
	public:

		// setters
		void setPosition(float x, float y);
		inline void setPosition(glm::fvec2 position) { setPosition(position.x, position.y); }
		inline void setPosition(const sf::Vector2f position) { setPosition(position.x, position.y); }
		void setRotation(float angle);
		void setScale(float x, float y);
		inline void setScale(float scale) { setScale(scale, scale); }
		inline void setScale(glm::fvec2 scale) { setScale(scale.x, scale.y); }
		inline void setScale(const sf::Vector2f scale) { setScale(scale.x, scale.y); }

		void move(float x, float y);
		inline void move(sf::Vector2f vect) { move( vect.x, vect.y ); }
		inline void move(glm::fvec2 vect) { move(vect.x, vect.y); }
		void rotate(float angle);
		void scale(float x, float y);
		inline void scale(sf::Vector2f vect) { scale(vect.x, vect.y); }
		inline void scale(glm::fvec2 vect) { scale(vect.x, vect.y); }

		void setSprite( Sprite* sprite );
		void setZIndex(int z_index);
		void setArea( Area* area = nullptr );

		inline void setVisible(bool visible) { m_visible = visible; }

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

	private:
		friend class Scene;
		friend class Application;

		inline void setScene(Scene* scene) { m_scene = scene; }

		static int s_object_count;
		int m_z_index = 0; // small val render first
		int m_id;
		bool m_visible = true;
		Scene* m_scene = nullptr;
		Application* m_applicaton = nullptr;
		Sprite* m_sprite = nullptr;
		Area* m_area = nullptr;
	};
}