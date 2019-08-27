#pragma once
#include "..//core.h"

#include "tinyxml2.h"
#include "..//Scene.h"
#include "..//misc/Texture.h"
#include "..//misc/Font.h"

namespace pe
{
	class AssetsReader
	{
	public:
		inline tinyxml2::XMLDocument& getDocument() { return m_doc; }

		void readTextures(std::map<int, Texture*>& texture_map);
		void readFonts(std::map<int, Font*>& font_map);
		void readSprites(std::map<int, Sprite*>& sprite_map, std::map<int, Texture*> *texture_map = nullptr);
		//void readBackground(std::map<int, Background*>& bg_map);
		//void readAnimation(std::map<int, Background*>& anim_map);
		//void readArea(std::map<int, Area*>& area_map);

	private:
		tinyxml2::XMLDocument m_doc;
	};
}