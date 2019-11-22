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

	void reloadSprite(bool reload_file = false);

	void render();

};