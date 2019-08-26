#pragma once
#include "..//core.h"

#include "tinyxml2.h"

#include "..//Scene.h"
#include "..//misc/Texture.h"

namespace pe
{
	class  AssetsFile
	{
	public:
		AssetsFile();

		inline tinyxml2::XMLDocument& getDocument() { return m_doc; }

		void addTexture( Texture* texture);
		void addSprite(Sprite* sprite);
		void addBackground(Background* bg);
		void addAnimation(Animation* anim);
		//void addArea(Area* area);

		
	private:
		tinyxml2::XMLDocument m_doc;
		
	};
}
