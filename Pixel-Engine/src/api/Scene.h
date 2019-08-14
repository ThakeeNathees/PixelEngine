#pragma once
#include "core.h"

#include "entities/Object.h"
#include "entities/Background.h"


namespace pe
{
	class PIXEL_ENGINE_API Scene
	{
	public:
		Scene(const char* name);
		~Scene();

		//setters
		void addObject(Object* object);
		void sortObjectsZIndex();
		void setBackground( Background* background);

		//getters
		inline const char* getName() { return m_name; }
		inline std::vector<Object*>& getObjects() { return m_objects; }
		inline Background* getBackground() { return m_background; }
		void setSceneWindowSize(glm::ivec2 window_size);

	private:
		const char* m_name;
		static bool sortCompare(Object* obj1, Object* obj2);
		std::vector<Object*> m_objects;
		glm::ivec2 m_window_size = glm::ivec2(-1, -1);
		Background* m_background = nullptr; // deleted by global game assets
	};
}