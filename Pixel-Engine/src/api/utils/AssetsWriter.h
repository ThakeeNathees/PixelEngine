#pragma once
#include "..//core.h"

#include "tinyxml2.h"
#include "..//Scene.h"
#include "..//misc/Texture.h"
#include "..//misc/Font.h"

namespace pe
{
	class  AssetsWriter
	{
	public:
		AssetsWriter();

		inline tinyxml2::XMLDocument& getDocument() { return m_doc; }

		void addTexture(::pe::Texture* texture);
		void addFont(::pe::Font* font);
		void addSprite(Sprite* sprite);
		void addBackground(Background* bg);
		void addAnimation(Animation* anim);
		void addArea(Area* area);

		
	private:
		tinyxml2::XMLDocument m_doc;
		
	};
}
