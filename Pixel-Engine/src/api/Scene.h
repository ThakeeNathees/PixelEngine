#pragma once
#include "core.h"

#include "entities/Object.h"
#include "entities/Background.h"

#include "misc/Drawable.h"

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
		inline void addSignal(Signal* signal) { m_signals.push_back(signal); }
		void addTimer(Timer* timer);
		void sortZIndex();
		void setBackground( Background* background);
		void setSceneWindowSize(glm::ivec2 window_size);

		void clear(); // clear signals and Timers

		//getters
		inline const std::string& getName() const { return m_name; }
		inline std::vector<Object*>& getObjects() { return m_objects; }
		inline const std::vector<pe::Drawable*> getDrawables() const { return m_drawables; }
		inline Background& getBackground() { return *m_background; }
		Object& getObject(const std::string& name);
		bool hasObject(const std::string& name);
		
		inline bool hasBackground() const { return m_background != nullptr; }

	private:
		friend class Application;
		std::string m_name;
		static bool sortCompare(pe::Drawable* obj1, pe::Drawable* obj2);
		std::vector<Object*> m_objects;
		std::vector<pe::Drawable*> m_drawables;
		std::vector<Signal*> m_signals;
		std::vector<Timer*> m_timers;
		glm::ivec2 m_window_size = glm::ivec2(-1, -1);
		Background* m_background = nullptr; // deleted by global assets
	};
}