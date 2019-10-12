#pragma once
#include "pch.h"

class ObjPropEditor
{
private:
	static ObjPropEditor* s_instance;
	static int s_tex_size;

	sf::RenderTexture m_render_texture;
	pe::Texture m_texture;
	pe::Sprite m_sprite;
	py::object* m_obj_tag;
	int m_path_dst_ind = 0; // 0- script path

	// object property
	char m_obj_name[1024] = {};
	char m_script_name[1024] = {};
	char m_script_path[2048] = {};
	int m_obj_type = 0; // 0 - means unknown , 1 - means py , 2 - cpp

	int m_z_index = 0;
	int m_visible = 1; // 0 -false, 1- true;
	int m_persistance = 0;



public:
	static ObjPropEditor* getinstance() {
		if (s_instance == nullptr) {
			s_instance = new ObjPropEditor();
			s_instance->m_render_texture.create(s_tex_size, s_tex_size);
		}
		return s_instance;
	}

	void reloadObj( bool reload_file = false ) {

		if (reload_file) m_obj_tag->attr("reload")();
		if (m_obj_tag->attr("hasSpriteTag")().cast<bool>()) {
			int tex_id = m_obj_tag->attr("getSpriteTextureId")().cast<int>();
			m_sprite.setTexture(*pe::Assets::getAsset<pe::Texture>(tex_id));
			auto rect = m_obj_tag->attr("getSpriteTextureRect")().cast<std::vector<int>>();
			m_sprite.setTextureRect(sf::IntRect(rect[0], rect[1], rect[2], rect[3]));
			auto frames = m_obj_tag->attr("getSpriteFrames")().cast<std::vector<int>>();
			m_sprite.setFrames(frames[0], frames[1], frames[2], frames[3]);
			m_sprite.setFrameIndex(frames[4]);

			bool is_height_min = (m_sprite.getTextureRect().width > m_sprite.getTextureRect().height);
			int spr_size = std::max(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);
			m_sprite.setScale(s_tex_size / (float)spr_size, s_tex_size / (float)spr_size);
			if (is_height_min) m_sprite.setPosition(0, (s_tex_size - m_sprite.getScale().x * m_sprite.getTextureRect().height) / 2);
			else m_sprite.setPosition((s_tex_size - m_sprite.getScale().x * m_sprite.getTextureRect().width) / 2, 0);

			// fill fields
			int i; const char* c;
			std::string buffer;
			buffer = m_obj_tag->attr("getName")().cast<std::string>();
			c = buffer.c_str(); i = 0;
			while (c[i])  m_obj_name[i] = c[i++]; m_obj_name[i] = 0;
			buffer = m_obj_tag->attr("getClassName")().cast<std::string>();
			c = buffer.c_str(); i = 0;
			while (c[i])  m_script_name[i] = c[i++]; m_obj_name[i] = 0;
			buffer = m_obj_tag->attr("getScriptPath")().cast<std::string>();
			c = buffer.c_str(); i = 0;
			while (c[i])  m_script_path[i] = c[i++]; m_script_path[i] = 0;
			
			m_obj_type = m_obj_tag->attr("getObjectType")().cast<int>();
			m_z_index = m_obj_tag->attr("getZindex")().cast<int>();
			m_visible = m_obj_tag->attr("isVisible")().cast<bool>();
			m_persistance = m_obj_tag->attr("isPersistence")().cast<bool>();

			

		}
	}

	void setObjTag(py::object* obj_tag) {
		m_obj_tag = obj_tag; 
		reloadObj();
	}

	void render();
};
