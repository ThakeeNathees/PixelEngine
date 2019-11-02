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

	void setSceneTag(py::object* scene_tag) {
		m_scene_tag = scene_tag;
		// TODO: reload scene
	}

private:
	ScenePropEditor() {}
	static ScenePropEditor* s_instance;

	sf::RenderTexture m_render_texture;
	py::object* m_scene_tag = nullptr;
};