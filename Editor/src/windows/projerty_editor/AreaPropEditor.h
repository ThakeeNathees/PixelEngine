#pragma once

#include "core/Resources.h"

class AreaPropEditor
{
private:
	AreaPropEditor(){}
	static AreaPropEditor* s_instance;
	py::object* m_obj_tag;
	sf::RenderTexture m_render_texture;
	pe::Sprite m_sprite;
	sf::ConvexShape m_area;

	static int s_tex_size;
	static int s_tex_margin;

public:
	bool m_open = false;
	static AreaPropEditor* getInstance() {
		if (!s_instance) {
			s_instance = new AreaPropEditor();
			s_instance->m_render_texture.create(s_tex_size + s_tex_margin, s_tex_size + s_tex_margin);
		}
		return s_instance;
	}

	void open(py::object* obj) {
		m_obj_tag = obj;
		reloadObj();
		m_open = true;
	}

	void reloadObj(bool reload_file = false);

	void render();
};
