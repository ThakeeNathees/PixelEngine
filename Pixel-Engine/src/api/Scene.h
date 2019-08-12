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

		//getters
		std::vector<Object*>& getObjects();

	private:
		std::vector<Object*> m_objects;
	};
}