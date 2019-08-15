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
		inline void setScale(glm::fvec2 scale) { setScale(scale.x, scale.y); }
		inline void setScale(const sf::Vector2f scale) { setScale(scale.x, scale.y); }

		void setSprite( Sprite* sprite );
		void setZIndex(int z_index);
		void setArea( Area* area );

		// getters
		inline Application* getApplication() const { return m_applicaton; }
		inline Scene* getScene() const  { return m_scene; }
		inline Area* getArea() const { return m_area; }
		inline Sprite* getSprite() const { return m_sprite; }
		inline int getZIndex() const { return m_z_index; }
		inline int getId() const { return m_id; }

	private:
		friend class Scene;
		friend class Application;

		inline void setScene(Scene* scene) { m_scene = scene; }
		static void applyTransform( sf::Transformable* to, sf::Transformable* from );

		static int s_object_count;
		int m_z_index = 0; // small val render first
		int m_id;
		Scene* m_scene = nullptr;
		Application* m_applicaton = nullptr;
		Sprite* m_sprite = nullptr;
		Area* m_area = nullptr;
	};
}