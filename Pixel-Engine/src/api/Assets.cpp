#include "pch.h"
#include "Assets.h"

namespace pe
{

	Assets::Assets() {}

	Assets::~Assets() { // TODO: add remove(any asset) functions
		for (auto tex : m_textures)
			delete tex.second;
		for (auto font : m_fonts)
			delete font.second;
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
	void Assets::addTexture(::pe::Texture* texture) {
		if (hasTexture(texture->getId())) return;
		m_textures[texture->getId()] = texture;
	}
	void Assets::addFont(::pe::Font* font) {
		if (hasFont(font->getId())) return;
		m_fonts[font->getId()] = font;
	}
	void Assets::addSprite(Sprite* sprite) {
		if (hasSprite(sprite->getId())) delete m_sprites[sprite->getId()];
		m_sprites[sprite->getId()] = sprite;
	}
	void Assets::addBackground(Background* background) {
		if (hasBackground(background->getId())) delete m_backgrounds[background->getId()];
		m_backgrounds[background->getId()] = background;
	}
	void Assets::addAnimation(Animation* animation) {
		if (hasAnimation(animation->getId())) delete m_animations[animation->getId()];
		m_animations[animation->getId()] = animation;
	}
	void Assets::addArea(Area* area) {
		if (hasArea(area->getId())) delete m_areas[area->getId()];
		m_areas[area->getId()] = area;
	}

	// getters
	bool Assets::hasTexture(int id) {
		return m_textures.find(id) != m_textures.end();
	}
	bool Assets::hasFont(int id) {
		return m_fonts.find(id) != m_fonts.end();
	}
	bool Assets::hasSprite(int id) {
		return m_sprites.find(id) != m_sprites.end();
	}
	bool Assets::hasBackground(int id) {
		return m_backgrounds.find(id) != m_backgrounds.end();
	}
	bool Assets::hasAnimation(int id) {
		return m_animations.find(id) != m_animations.end();
	}
	bool Assets::hasArea(int id) {
		return m_areas.find(id) != m_areas.end();
	}

	bool Assets::hasTexture(const std::string& name) {
		for (auto tex : m_textures) { if (tex.second->getName() == name) return true; }
		return false;
	}
	bool Assets::hasFont(const std::string& name) {
		for (auto font : m_fonts) { if (font.second->getName() == name) return true; }
		return false;
	}
	bool Assets::hasSprite(const std::string& name) {
		for (auto spr : m_sprites) { if (spr.second->getName() == name) return true; }
		return false;
	}
	bool Assets::hasBackground(const std::string& name) {
		for (auto area : m_areas) { if (area.second->getName() == name) return true; }
		return false;
	}
	bool Assets::hasAnimation(const std::string& name) {
		for (auto anim : m_animations) { if (anim.second->getName() == name) return true; }
	}
	bool Assets::hasArea(const std::string& name) {
		for (auto area : m_areas) { if (area.second->getName() == name) return true; }
		return false;
	}

	Texture* Assets::getTexture(int id) {
		assert(hasTexture(id) && "invalid texture path to get!");
		return m_textures[id];
	}
	Font* Assets::getFont(int id) {
		assert(hasFont(id) && "invalid font path to get!");
		return m_fonts[id];
	}
	Sprite* Assets::getSprite(int id) {
		assert(hasSprite(id) && "invalid sprite name to get!");
		return m_sprites[id];
	}
	Background* Assets::getBackground(int id) {
		assert( hasBackground(id) && "invalid background name to get!" );
		return m_backgrounds[id];
	}
	Animation* Assets::getAnimation(int id) {
		assert(hasAnimation(id) && "invalid animation name to get!");
		return m_animations[id];
	}
	Area* Assets::getArea(int id) {
		assert(hasArea(id) && "invalid area name to get!");
		return m_areas[id];
	}

	Texture* Assets::getTexture(const std::string& name) {
		for (auto tex : m_textures) if (tex.second->getName() == name) return tex.second;
		assert( false && "invalid texture name to get!" );
	}
	Font* Assets::getFont(const std::string& name) {
		for (auto font : m_fonts) if (font.second->getName() == name) return font.second;
		assert( false && "invalid font name to get!" );
	}
	Sprite* Assets::getSprite(const std::string& name) {
		for (auto spr : m_sprites) if (spr.second->getName() == name) return spr.second;
		assert( false && "invalid sprite name to get!" );
	}
	Background* Assets::getBackground(const std::string& name) {
		for (auto bg : m_backgrounds) if (bg.second->getName() == name) return bg.second;
		assert( false && "invalid background name to get!" );
	}
	Animation* Assets::getAnimation(const std::string& name) {
		for (auto anim : m_animations) if (anim.second->getName() == name) return anim.second;
		assert( false && "invalid animation name to get!" );
	}
	Area* Assets::getArea(const std::string& name) {
		for (auto area : m_areas) if (area.second->getName() == name) return area.second;
		assert( false && "invalid area name to get!" );
	}
	
}