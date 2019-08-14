#pragma once
#include "..//core.h"

#include "Sprite.h"
#include "Area.h"


namespace pe
{
    class Scene;
	class PIXEL_ENGINE_API Object
	{
	public:
		Object();
		~Object();

		// virtual functions
		inline virtual void init() {};
		inline virtual void process(double dt) {};
		inline virtual bool input(sf::Event& event) { return false; } // return if event handled ?
		inline virtual void draw( sf::RenderWindow* window ) {
			window->draw(*this->getSprite());
		}

		// setters
		void setPosition( glm::vec2 position );
		void setPosition( float x, float y );
		void setSprite( Sprite* sprite );
		void setZIndex(int z_index);
		void setArea( Area* area );

		// getters
		inline glm::vec2 getPosition() const { return m_position; }
		inline Sprite* getSprite() const { return m_sprite; }
		inline int getZIndex() const { return m_z_index; }
		inline int getId() const { return m_id; }
		inline Scene* getScene() { return m_scene; }
		inline Area* getArea() { return m_area; }

	private:
		friend class Scene;
		inline void setScene(Scene* scene) { m_scene = scene; }

		static int s_object_count;
		int m_id;
		Sprite* m_sprite;
		glm::vec2 m_position = glm::vec2(0,0);
		int m_z_index = 0; // small val render first
		Scene* m_scene;
		Area* m_area;
	};
}