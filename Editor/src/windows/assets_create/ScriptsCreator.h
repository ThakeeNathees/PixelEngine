#pragma once

#include "core/CLI.h"
#include "windows/ExplorerPopup.h"

class ScriptCreator
{
public:
	bool m_is_script_created = false; // let obj_creater know to get name and path
	char m_script_name[1024] = {};
	char m_script_path[1024] = {};
	std::string m_script_path_name=""; // full path name of created file

private:
	ScriptCreator() {}
	static ScriptCreator* s_instance;

	bool m_popen = false;
	int m_script_type = 0; // 0: python, 1: cpp;
	int m_template_type = 0; // 0 : default, 1:no comment 2: empty
	int m_parent_window = -1; // 0 - obj creator, 1 - obj editor

public:
	static ScriptCreator* getInstance() {
		if (s_instance == nullptr) s_instance = new ScriptCreator();
		return s_instance;
	}

	void open() { m_popen = true; }
	bool isOpen() { return m_popen == true; }

	void setParentWindow(int parent_window) {
		m_parent_window = parent_window;
	}
	int getParentWindow() const {
		return m_parent_window;
	}

	void clearValues() {
		m_script_name[0] = '\0';
		m_script_path[0] = '\0';
	}

	void render();
};