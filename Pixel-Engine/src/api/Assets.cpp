#include "pch.h"
#include "Assets.h"

namespace pe
{
	// setters
	void Assets::addSprite(Sprite* sprite) {
		if (hasSprite(sprite->getName())) delete m_sprites[sprite->getName()];
		m_sprites[sprite->getName()] = sprite;
	}
	void Assets::addBackground(Background* background) {
		if (hasBackground(background->getName())) delete m_backgrounds[background->getName()];
		m_backgrounds[background->getName()] = background;
	}
	void Assets::addAnimation(Animation* animation) {
		if (hasAnimation(animation->getName())) delete m_animations[animation->getName()];
		m_animations[animation->getName()] = animation;
	}

	// getters
	bool Assets::hasSprite(const std::string& name) {
		return m_sprites.find(name) != m_sprites.end();
	}
	bool Assets::hasBackground(const std::string& name) {
		return m_backgrounds.find(name) != m_backgrounds.end();
	}
	bool Assets::hasAnimation(const std::string& name) {
		return m_animations.find(name) != m_animations.end();
	}


	Sprite& Assets::getSprite(const std::string& name) {
		assert(hasSprite(name) && "invalid sprite name to get!");
		return *m_sprites[name];
	}
	Background& Assets::getBackground(const std::string& name) {
		assert( hasBackground(name) && "invalid background name to get!" );
		return *m_backgrounds[name];
	}
	Animation& Assets::getAnimation(const std::string& name) {
		assert(hasAnimation(name) && "invalid animation name to get!");
		return *m_animations[name];
	}
	
}