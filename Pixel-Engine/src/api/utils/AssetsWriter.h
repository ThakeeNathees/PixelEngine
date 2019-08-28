#pragma once
#include "..//core.h"

#include "..//Scene.h"
#include "..//misc/Texture.h"
#include "..//misc/Font.h"

namespace tinyxml2{ class XMLDocument; }

namespace pe
{
	class Assets;

	class  AssetsWriter
	{
	public:
		AssetsWriter();

		void save(const char* path);
		void addAssets( Assets& assets );

	private:		
		void addTexture( Texture* texture);
		void addFont( Font* font);
		void addArea(Area* area);
		void addSprite(Sprite* sprite);
		void addBackground(Background* bg);
		void addAnimation(Animation* anim);
		
		tinyxml2::XMLDocument* m_doc;
		
	};
}
