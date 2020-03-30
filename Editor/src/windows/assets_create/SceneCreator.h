#pragma once

#include "core/CLI.h"
#include "windows/ExplorerPopup.h"

class SceneCreator
{
private:
	bool m_open = false;
	std::string m_scene_path_name;
	bool m_is_scene_created = false;
	char m_scene_name[1024] = {};
	char m_scene_path[1024] = {};
	py::module m_py_scn_maker;

	SceneCreator() {
		m_py_scn_maker = py::module::import("scene_maker");
	}
	static SceneCreator* s_instance;

public:
	static SceneCreator* getInstance() {
		if (s_instance == nullptr) s_instance = new SceneCreator();
		return s_instance;
	}

	void open() { m_open = true; }
	bool isOpen() { return m_open == true; }

	void clearValues() {
		m_scene_name[0] = '\0';
		m_scene_path[0] = '\0';
	}

	void render();
};