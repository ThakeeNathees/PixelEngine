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
		Scene(const Scene& other) = delete;
		~Scene();

		//setters
		void addObject(Object* object);
		void sortObjectsZIndex();
		void setBackground( Background* background);
		inline void setDebugMode(bool is_debug_mode) { m_is_debug_mode = is_debug_mode; }
		void setSceneWindowSize(glm::ivec2 window_size);


		//getters
		inline const char* getName() { return m_name; }
		inline std::vector<Object*>& getObjects() { return m_objects; }
		inline Background& getBackground() { return *m_background; }
		
		inline bool isDebugMode() { return m_is_debug_mode; }
		inline bool hasBackground() const { return m_background != nullptr; }

	private:
		bool m_is_debug_mode = false;
		const char* m_name;
		static bool sortCompare(Object* obj1, Object* obj2);
		std::vector<Object*> m_objects;
		glm::ivec2 m_window_size = glm::ivec2(-1, -1);
		Background* m_background = nullptr; // deleted by global game assets
	};
}