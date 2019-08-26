#pragma once
#include "..//core.h"

#include "..//Scene.h"
#include "tinyxml2.h"

namespace pe
{
	class  AssetsFile
	{
	public:
		AssetsFile();

		inline tinyxml2::XMLDocument& getDocument() { return m_doc; }

		void addTexture(sf::Texture* texture, const char* path);
		void addSprite(Sprite* sprite);
		//void addBackground(Background* bg);
		//void addAnimation(Animation* anim);
		//void addArea(Area* area);


		
	private:
		tinyxml2::XMLDocument m_doc;
		
	};
}
