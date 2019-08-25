#pragma once
#include "core.h"

#include "entities/Sprite.h"
#include "entities/Background.h"
#include "entities/Animation.h"
#include "entities/Area.h"


namespace pe
{
	class PIXEL_ENGINE_API Assets
	{
	public:
		~Assets();

		// setters
		void addTexture(sf::Texture* texture, const std::string& path);
		void addSprite(Sprite* sprite);
		void addBackground(Background* background);
		void addAnimation(Animation* animation);
		void addArea( Area* area );

		// TODO: delete queue, fonts

		// getters
		bool hasTexture(const std::string& path);
		bool hasSprite(const std::string& name);
		bool hasBackground(const std::string& name);
		bool hasAnimation(const std::string& name);
		bool hasArea(const std::string& area);

		sf::Texture* getTexture(const std::string& path);
		Sprite* getSprite(const std::string& name);
		Background* getBackground(const std::string& name);
		Animation* getAnimation(const std::string& name);
		Area* getArea( const std::string& area );

	private:
		std::map<std::string, sf::Texture*> m_textures; // string=path
		std::map<std::string, Sprite*> m_sprites;
		std::map<std::string, Background*>m_backgrounds;
		std::map<std::string, Animation*>m_animations;
		std::map<std::string, Area*> m_areas;
	};
}