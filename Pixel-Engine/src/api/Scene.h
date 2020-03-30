#pragma once
#include "core.h"

// all the assets are included
#include "entities/Object.h"
#include "entities/Background.h"
#include "misc/Font.h"
#include "misc/Text.h"


namespace pe
{
	class PIXEL_ENGINE_API Scene : public Asset
	{
	public:
		Scene(std::string name);
		Scene(int id = -1);
		Scene(const Scene& other) = delete;
		~Scene();

		//setters
		void addObject(Object* object);
		inline void addSignal(Signal* signal) { m_signals.push_back(signal); }
		void addTimer(Timer* timer);
		void sortZIndex();
		void setBackground( Background* background);
		//void setSceneWindowSize(sf::Vector2i window_size);
		inline void setName(const std::string& name) override { m_name = name; }

		void clear(); // clear signals and Timers

		//getters
		inline const std::string& getName() const override { return m_name; }
		inline std::vector<Object*>& getObjects() { return m_objects; }
		inline const std::vector<pe::Drawable*> getDrawables() const { return m_drawables; }
		inline Background* getBackground() { return m_background; }
		Object* getObject(const std::string& name);
		inline int getId() const override { return m_id; }
		inline Asset::Type getType() const override { return Asset::Type::Scene; }


	private:
		friend class Application;
		friend class FileHandler;
		static bool sortCompare(pe::Drawable* obj1, pe::Drawable* obj2);
		static int s_scene_count;
		static int s_next_id;

		std::string m_name;
		int m_id;
		//sf::Vector2i m_window_size = sf::Vector2i(-1, -1);
		Background* m_background = nullptr;
		std::vector<Object*> m_objects;
		std::vector<pe::Drawable*> m_drawables;
		std::vector<Signal*> m_signals;
		std::vector<Timer*> m_timers;
	};
}