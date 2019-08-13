#pragma once
#include "core.h"

#include "entities/Object.h"


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
		void loadBackgroundTexture( std::string path );
		inline void setBgVisible(bool visible) { m_bg_visible = visible; }

		//getters
		inline const char* getName() { return m_name; }
		inline std::vector<Object*>& getObjects() { return m_objects; }
		inline sf::Sprite& getBackground() { return m_background; }
		inline bool getBgVisible() const { return m_bg_visible; }

	private:
		const char* m_name;
		static bool sortCompare(Object* obj1, Object* obj2);
		std::vector<Object*> m_objects;
		bool m_bg_visible = false;
		sf::Sprite m_background;
		sf::Texture m_bg_texture;
	};
}