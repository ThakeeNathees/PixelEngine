#pragma once
#include "..//core.h"

#include "..//Scene.h"
#include "..//misc/Texture.h"
#include "..//misc/Font.h"


namespace tinyxml2 { class XMLDocument; }

namespace pe
{
	class Assets;

	class AssetsReader
	{
	public:
		AssetsReader(const char* path);
		void loadFile(const char* path);
		void readAssets( Assets& assets );

	private:
		void readTextures(std::map<int, Texture*>& texture_map);
		void readFonts(std::map<int, Font*>& font_map);
		void readArea(std::map<int, Area*>& area_map);
		void readSprites(std::map<int, Sprite*>& sprite_map, std::map<int, Texture*> *texture_map = nullptr);
		void readBackground(std::map<int, Background*>& bg_map, std::map<int, Texture*>* texture_map = nullptr);
		void readAnimation(std::map<int, Animation*>& anim_map);

		tinyxml2::XMLDocument* m_doc;
	};
}