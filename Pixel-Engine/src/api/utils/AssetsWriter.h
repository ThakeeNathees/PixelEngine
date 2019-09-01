#pragma once
#include "..//core.h"

#include "..//Scene.h"
#include "..//misc/Texture.h"
#include "..//misc/Font.h"

namespace tinyxml2{ class XMLDocument; }

namespace pe
{
	class Assets;

	class PIXEL_ENGINE_API AssetsWriter
	{
	public:
		AssetsWriter();

		void save(const char* path);
		void addAssets();
		void addAssets(std::map<int, Asset*>& asset_map);
		void addAssets(std::vector<int>& assets_vec);
		void addAsset(int id);
		void addAsset(Asset* asset);

	private:		
		void addTexture( Texture* texture);
		void addFont( Font* font);
		void addArea(Area* area);
		void addSprite(Sprite* sprite);
		void addBackground(Background* bg);
		void addAnimation(Animation* anim);
		void addObject(Object* obj);
		
		tinyxml2::XMLDocument* m_doc;
		
	};
}
