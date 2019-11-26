#pragma once

#include "core/CLI.h"

class ScenePropEditor
{
public:
	bool m_open = true;

	static ScenePropEditor* getInstance() {
		if (!s_instance) {
			s_instance = new ScenePropEditor();
			s_instance->m_render_texture.create(600, 400- s_scene_height_offset);
			s_instance->m_render_texture.clear(CLI::getInstance()->getPeproj().default_bg_color);
			s_instance->m_scene_trans.setPosition(100,100);
		}
		return s_instance;
	}

	void render();
	void handleEvent(sf::Event& event);

	void open(py::object* scn_tag) {
		setSceneTag(scn_tag);
		m_open = true;
	}

	void setSceneTag(py::object* scn_tag) {
		m_scene_tag = scn_tag;
		reloadScene();
	}

	void reloadScene(bool reload_file = false);


private:
	ScenePropEditor() {}
	void drawAxisLines();

	static ScenePropEditor* s_instance;
	static sf::Color s_color_axis;
	static sf::Color s_color_scene_area;
	static int s_scene_height_offset;

	sf::RenderTexture m_render_texture;
	py::object* m_scene_tag = nullptr;

	bool m_is_focus				= false;
	bool m_window_size_changed	= false;
	ImVec2 m_window_size		= ImVec2(0, 0);
	sf::Transformable m_scene_trans;

	sf::Vector2f m_mouse_pos;
	
};
