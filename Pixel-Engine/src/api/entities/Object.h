#pragma once
#include "..//core.h"

#include "Sprite.h"
#include "Area.h"


namespace pe
{
    class Scene;
	class PIXEL_ENGINE_API Object : public sf::Transformable, public sf::Drawable
	{
	public:
		Object();
		~Object();

		// virtual functions
		inline virtual void init() {};
		inline virtual void process(double dt) {};
		inline virtual bool input(sf::Event& event) { return false; } // return if event handled ?
		inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
			states.transform *= getTransform(); // apply transform to member drawables
			target.draw(*getSprite(), states);
			// debug:
			if (m_area != nullptr)
			target.draw( *(m_area->getShape()), states );
		}

		// setters
		void setSprite( Sprite* sprite );
		void setZIndex(int z_index);
		void setArea( Area* area );

		// getters
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
		//glm::vec2 m_position = glm::vec2(0,0);
		int m_z_index = 0; // small val render first
		Scene* m_scene;
		Area* m_area;
	};
}