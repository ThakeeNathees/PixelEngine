#pragma once
#include "core.h"

#include "entities/Object.h"


namespace pe
{
	class PIXEL_ENGINE_API Scene
	{
	public:
		~Scene();

		//setters
		void addObject(Object* object);
		void sortObjectsZIndex();

		//getters
		inline std::vector<Object*>& getObjects() { return m_objects; }
		inline sf::Texture& getBackground() { return m_background; }

	private:
		static bool sortCompare(Object* obj1, Object* obj2);
		std::vector<Object*> m_objects;
		sf::Texture m_background; // TODO: create [/]getter []setter and []default place holder texture
	};
}