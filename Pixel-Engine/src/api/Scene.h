#pragma once
#include "core.h"

#include "entities/Object.h"
#include "entities/Background.h"


namespace pe
{
	class PIXEL_ENGINE_API Scene
	{
	public:
		Scene(std::string name);
		Scene(const Scene& other) = delete;
		~Scene();

		//setters
		void addObject(Object* object);
		void sortObjectsZIndex();
		void setBackground( Background* background);
		void setSceneWindowSize(glm::ivec2 window_size);
		inline void addSignals(Signal* signal) { m_signals.push_back(signal); }


		//getters
		inline const std::string& getName() const { return m_name; }
		inline std::vector<Object*>& getObjects() { return m_objects; }
		inline Background& getBackground() { return *m_background; }
		Object& getObject(const std::string& name);
		bool hasObject(const std::string& name);
		
		inline bool hasBackground() const { return m_background != nullptr; }

	private:
		friend class Application;
		std::string m_name;
		static bool sortCompare(Object* obj1, Object* obj2);
		std::vector<Object*> m_objects;
		std::vector<Signal*> m_signals;
		glm::ivec2 m_window_size = glm::ivec2(-1, -1);
		Background* m_background = nullptr; // deleted by global assets
	};
}