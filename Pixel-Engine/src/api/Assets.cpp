#include "pch.h"
#include "Assets.h"

namespace pe
{

	Assets::Assets() {
		
	}

	Assets::~Assets() { // TODO: add remove(any asset) functions
		for (auto tex : m_textures)
			delete tex.second;
		for (auto spr : m_sprites)
			delete spr.second;
		for (auto bg : m_backgrounds)
			delete bg.second;
		for (auto anim : m_animations)
			delete anim.second;
		for (auto area : m_areas)
			delete area.second;
	}

	// setters
	void Assets::addTexture(sf::Texture* texture, const std::string& path) {
		if (hasTexture(path)) return;
		m_textures[path] = texture;
	}
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
	void Assets::addArea(Area* area) {
		if (hasArea(area->getName())) delete m_areas[area->getName()];
		m_areas[area->getName()] = area;
	}

	// getters
	bool Assets::hasTexture(const std::string& path) {
		return m_textures.find(path) != m_textures.end();
	}
	bool Assets::hasSprite(const std::string& name) {
		return m_sprites.find(name) != m_sprites.end();
	}
	bool Assets::hasBackground(const std::string& name) {
		return m_backgrounds.find(name) != m_backgrounds.end();
	}
	bool Assets::hasAnimation(const std::string& name) {
		return m_animations.find(name) != m_animations.end();
	}
	bool Assets::hasArea(const std::string& name) {
		return m_areas.find(name) != m_areas.end();
	}

	sf::Texture* Assets::getTexture(const std::string& path) {
		assert(hasTexture(path) && "invalid texture path to get!");
		return m_textures[path];

	}
	Sprite* Assets::getSprite(const std::string& name) {
		assert(hasSprite(name) && "invalid sprite name to get!");
		return m_sprites[name];
	}
	Background* Assets::getBackground(const std::string& name) {
		assert( hasBackground(name) && "invalid background name to get!" );
		return m_backgrounds[name];
	}
	Animation* Assets::getAnimation(const std::string& name) {
		assert(hasAnimation(name) && "invalid animation name to get!");
		return m_animations[name];
	}
	Area* Assets::getArea(const std::string& name) {
		assert(hasArea(name) && "invalid area name to get!");
		return m_areas[name];
	}
	
}