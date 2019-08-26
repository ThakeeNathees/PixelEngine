#include "pch.h"
#include "AssetsFile.h"

namespace pe
{
	AssetsFile::AssetsFile() {
		auto assets = m_doc.NewElement("assets");
		m_doc.InsertFirstChild(assets);

		auto textures = m_doc.NewElement("textures");
		auto sprites = m_doc.NewElement("sprites");
		auto backgrounds = m_doc.NewElement("backgrounds");
		auto animations = m_doc.NewElement("animations");
		auto areas = m_doc.NewElement("areas");
		// fonts, tile map, ...

		assets->InsertEndChild(textures);
		assets->InsertEndChild(sprites);
		assets->InsertEndChild(backgrounds);
		assets->InsertEndChild(animations);
		assets->InsertEndChild(areas);

		Sprite* sp = new Sprite() ;
		//sp->setFrames(12, 21, 1, 2);
		//sp->setFrameIndex(2);
		addSprite(sp);
		m_doc.SaveFile("assets_test.xml");
	}

	void AssetsFile::addTexture(sf::Texture* texture, const char* path) {
		auto textures = m_doc.FirstChildElement()->FirstChildElement("textures");
		auto texture_tag = m_doc.NewElement("texture");
		textures->InsertEndChild(texture_tag);

		texture_tag->SetAttribute("path", path);
		auto prop = m_doc.NewElement("properties");
		texture_tag->InsertEndChild(prop);
		prop->SetAttribute("smooth", texture->isSmooth());
		prop->SetAttribute("repeat", texture->isRepeated());
	}

	void AssetsFile::addSprite(Sprite* sprite) {
		auto sprites = m_doc.FirstChildElement()->FirstChildElement("sprites");
		auto sprite_tag = m_doc.NewElement("sprite");
		sprites->InsertEndChild(sprite_tag);

		sprite_tag->SetAttribute("name", sprite->getName().c_str());
		auto texture_path_tag = m_doc.NewElement("texture_path");
		sprite_tag->InsertEndChild(texture_path_tag);
		texture_path_tag->SetText(sprite->getTexturePath().c_str());

		auto frames_tag = m_doc.NewElement("frames");
		sprite_tag->InsertEndChild(frames_tag);
		frames_tag->SetAttribute("x", sprite->getFrames().x);
		frames_tag->SetAttribute("y", sprite->getFrames().y);
		frames_tag->SetAttribute("offset_x", sprite->getFrames().z);
		frames_tag->SetAttribute("offset_y", sprite->getFrames().w);

		auto frame_tag = m_doc.NewElement("frame");
		sprite_tag->InsertEndChild(frame_tag);
		frame_tag->SetAttribute("index", sprite->getCurrentFrame());
	}

}