#pragma once
#include "core.h"

#include "entities/Sprite.h"
#include "entities/Background.h"
#include "entities/Animation.h"
#include "entities/Area.h"

#include "misc/Texture.h"
#include "misc/Font.h"

#include "utils/AssetsWriter.h"


namespace pe
{
	class PIXEL_ENGINE_API Assets
	{
	public:
		Assets();
		~Assets();

		Texture*	newTexture()							{ Texture* texture = new Texture(); addTexture(texture); return texture; }
		Font*		newFont()								{ Font* font = new Font(); addFont(font); return font; }
		Area*		newArea()								{ Area* area = new Area(); addArea(area); return area; }
		Sprite*		newSprite()								{ Sprite* sprite = new Sprite(); addSprite(sprite); return sprite; }
		Background* newBackground()							{ Background* bg = new Background(); addBackground(bg); return bg; }
		Animation*	newAnimation()							{ Animation* anim = new Animation(); addAnimation(anim); return anim; }

		Texture*	newTexture(const std::string& name)		{ Texture* texture = new Texture(name); addTexture(texture); return texture; }
		Font*		newFont(const std::string& name)		{ Font* font = new Font(name); addFont(font); return font; }
		Area*		newArea(const std::string& name)		{ Area* area = new Area(name); addArea(area); return area; }
		Sprite*		newSprite(const std::string& name)		{ Sprite* sprite = new Sprite(name); addSprite(sprite); return sprite; }
		Background* newBackground(const std::string& name)	{ Background* bg = new Background(name); addBackground(bg); return bg; }
		Animation*	newAnimation(const std::string& name)	{ Animation* anim = new Animation(name); addAnimation(anim); return anim; }

		// setters
		void addTexture(Texture* texture);
		void addFont(Font* font);
		void addArea( Area* area );
		void addSprite(Sprite* sprite);
		void addBackground(Background* background);
		void addAnimation(Animation* animation);
		// add text, object, scene, tilemap

		// TODO: delete queue, fonts

		// getters
		bool hasTexture(const std::string& path);
		bool hasFont(const std::string& path);
		bool hasArea(const std::string& area);
		bool hasSprite(const std::string& name);
		bool hasBackground(const std::string& name);
		bool hasAnimation(const std::string& name);

		bool hasTexture(int id);
		bool hasFont(int id);
		bool hasArea(int id);
		bool hasSprite(int id);
		bool hasBackground(int id);
		bool hasAnimation(int id);

		
		Texture* getTexture(const std::string& path);
		Font* getFont(const std::string& path);
		Area* getArea( const std::string& area );
		Sprite* getSprite(const std::string& name);
		Background* getBackground(const std::string& name);
		Animation* getAnimation(const std::string& name);
		

		Texture* getTexture(int id);
		Font* getFont(int id);
		Area* getArea(int id);
		Sprite* getSprite(int id);
		Background* getBackground(int id);
		Animation* getAnimation(int id);

	private:
		friend class AssetsReader;
		friend class AssetsWriter;
		std::map<int, Texture*> m_textures;
		std::map<int, Font*> m_fonts;
		std::map<int, Area*> m_areas;
		std::map<int, Sprite*> m_sprites;
		std::map<int, Background*>m_backgrounds;
		std::map<int, Animation*>m_animations;
	};
}