#pragma once
#include "core/Resources.h"

class SpritePropEditor
{

private:
	static SpritePropEditor* s_instance;
	static int s_tex_size;
	SpritePropEditor(){}
	py::object* m_obj_tag;
	sf::RenderTexture m_render_texture;
	pe::Sprite m_sprite;
	const char* m_tex_names[10000] = {};
	int m_ind = 0; // for indexing textures
	int x = 1, y = 1, offset_x = 0, offset_y = 0, ind = 0;

public:
	bool m_open = false;

	static SpritePropEditor* getInstance() {
		if (!s_instance) {
			s_instance = new SpritePropEditor();
			s_instance->m_render_texture.create(s_tex_size, s_tex_size);
		}
		return s_instance;
	}

	void open(py::object* obj_tag) {
		setObjTag(obj_tag);
		m_open = true;
	}

	void setObjTag(py::object* obj_tag) {
		m_obj_tag = obj_tag;
		reloadSprite();
	}

	void reloadSprite(bool reload_file = false) {
		if (reload_file) m_obj_tag->attr("reload")();
		if (m_obj_tag->attr("hasSpriteTag")().cast<bool>()) {
			int tex_id = m_obj_tag->attr("getSpriteTextureId")().cast<int>();
			if (tex_id >= 0) {
				m_sprite.setTexture(*pe::Assets::getAsset<pe::Texture>(tex_id),true);
				//auto rect = m_obj_tag->attr("getSpriteTextureRect")().cast<std::vector<int>>();
				//m_sprite.setTextureRect(sf::IntRect(rect[0], rect[1], rect[2], rect[3]));
				auto frames = m_obj_tag->attr("getSpriteFrames")().cast<std::vector<int>>();
				x = frames[0]; y = frames[1]; offset_x = frames[2]; offset_y = frames[3]; ind = frames[4];
				m_sprite.setFrames(frames[0], frames[1], frames[2], frames[3]);
				m_sprite.setFrameIndex(frames[4]);
			}
			else {
				auto texture = pe::Texture();
				m_sprite.setTexture(texture, true);
			}
			bool is_height_min = (m_sprite.getTextureRect().width > m_sprite.getTextureRect().height);
			int spr_size = std::max(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);
			m_sprite.setScale(s_tex_size / (float)spr_size, s_tex_size / (float)spr_size);
			if (is_height_min) m_sprite.setPosition(0, (s_tex_size - m_sprite.getScale().x * m_sprite.getTextureRect().height) / 2);
			else m_sprite.setPosition((s_tex_size - m_sprite.getScale().x * m_sprite.getTextureRect().width) / 2, 0);
		}
		else {
			m_sprite = pe::Sprite();
		}
	}

	void render();

};