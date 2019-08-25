#pragma once
#include "core.h"

#include "entities/Sprite.h"
#include "entities/Background.h"
#include "entities/Animation.h"

#include "pch.h"

namespace pe
{
	class PIXEL_ENGINE_API Assets
	{
	public:
		// setters
		void addSprite(Sprite* sprite);
		void addBackground(Background* background);
		void addAnimation(Animation* animation);

		// TODO: delete queue, fonts

		// getters
		bool hasSprite(const std::string& name);
		bool hasBackground(const std::string& name);
		bool hasAnimation(const std::string& name);

		Sprite& getSprite(const std::string& name);
		Background& getBackground(const std::string& name);
		Animation& getAnimation(const std::string& name);

	private:
		std::map<std::string, Sprite*> m_sprites;
		std::map<std::string, Background*>m_backgrounds;
		std::map<std::string, Animation*>m_animations;
	};
}