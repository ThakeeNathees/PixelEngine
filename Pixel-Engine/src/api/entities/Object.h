#pragma once
#include "..//core.h"

#include "Sprite.h"
#include "Area.h"


namespace pe
{
	// forward class declaration
	extern class Scene;
	//extern bool Scene::isDebugMode();


	class PIXEL_ENGINE_API Object : public sf::Transformable, public sf::Drawable
	{
	public:
		Object();
		~Object();

		// virtual functions
		inline virtual void init() {};
		inline virtual void process(double dt) {};
		inline virtual bool input(sf::Event& event) { return false; } // return if event handled ?
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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
		int m_z_index = 0; // small val render first
		int m_id;
		Scene* m_scene = nullptr;
		Sprite* m_sprite = nullptr;
		Area* m_area = nullptr;
	};
}