#include "pch.h"
#include "AssetsReader.h"

namespace pe
{
	void AssetsReader::readTextures(std::map<int, Texture*>& texture_map) {
		auto textures = m_doc.FirstChildElement()->FirstChildElement("textures");
		for (auto texture_tag = textures->FirstChildElement(); texture_tag != NULL; texture_tag = texture_tag->NextSiblingElement()) {
			Texture* texture = new Texture();
			texture->setName(texture_tag->Attribute("name") );
			texture->m_id = texture_tag->IntAttribute("id");
			texture->setSmooth(texture_tag->BoolAttribute("smooth") );
			texture->setRepeated(texture_tag->BoolAttribute("repeat") );
			std::string  path = texture_tag->GetText();
			if (path != "") {
				texture->loadFromFile(path);
			}
			texture_map[texture->getId()] = texture;
		}
	}

	void AssetsReader::readFonts(std::map<int, Font*>& font_map) {
		auto fonts = m_doc.FirstChildElement()->FirstChildElement("fonts");
		for (auto font_tag = fonts->FirstChildElement(); font_tag != NULL; font_tag = font_tag->NextSiblingElement()) {
			Font* font = new Font();
			font->setName(font_tag->Attribute("name"));
			font->m_id = font_tag->IntAttribute("id");
			std::string path = font_tag->GetText();
			if (path != "") {
				font->loadFromFile(path);
			}
			font_map[font->m_id] = font;
		}
	}

	void AssetsReader::readSprites(std::map<int, Sprite*>& sprite_map, std::map<int, Texture*>* texture_map) {
		auto sprites = m_doc.FirstChildElement()->FirstChildElement("sprites");
		for (auto spr_tag = sprites->FirstChildElement(); spr_tag!= NULL; spr_tag = spr_tag->NextSiblingElement()) {
			Sprite* sprite = new Sprite();
			sprite->setName(spr_tag->Attribute("name"));
			sprite->m_id = spr_tag->IntAttribute("id");
			
			auto tex_tag = spr_tag->FirstChildElement("texture");
			if (tex_tag) {
				if (texture_map != nullptr) {
					int id = tex_tag->IntAttribute("id");
					assert((*texture_map)[id] != NULL && "can't find texture for the sprite");
					sprite->setTexture((*texture_map)[id]);
				}
				else if (sprite->m_texture != nullptr) { sprite->m_texture->m_id = tex_tag->IntAttribute("id"); }
				sf::IntRect rect;
				rect.left = spr_tag->FirstChildElement("texture_rect")->IntAttribute("left");
				rect.top = spr_tag->FirstChildElement("texture_rect")->IntAttribute("top");
				rect.width = spr_tag->FirstChildElement("texture_rect")->IntAttribute("width");
				rect.height = spr_tag->FirstChildElement("texture_rect")->IntAttribute("height");
				sprite->setTextureRect(rect);

				glm::ivec4 frames;
				frames.x = spr_tag->FirstChildElement("frames")->IntAttribute("x");
				frames.y = spr_tag->FirstChildElement("frames")->IntAttribute("y");
				frames.z = spr_tag->FirstChildElement("frames")->IntAttribute("offset_x");
				frames.w = spr_tag->FirstChildElement("frames")->IntAttribute("offset_y");
				int index = spr_tag->FirstChildElement("frames")->IntAttribute("index");
				sprite->setFrames(frames);
				sprite->setFrameIndex(index);
			}

			sprite_map[sprite->m_id] = sprite;
		}
	}
}