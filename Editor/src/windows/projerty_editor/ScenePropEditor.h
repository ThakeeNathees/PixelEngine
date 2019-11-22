#pragma once

class ScenePropEditor
{
public:
	bool m_open = true;

	static ScenePropEditor* getInstance() {
		if (!s_instance) {
			s_instance = new ScenePropEditor();
		}
		return s_instance;
	}

	void render();

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
	static ScenePropEditor* s_instance;

	sf::RenderTexture m_render_texture;
	py::object* m_scene_tag = nullptr;
};