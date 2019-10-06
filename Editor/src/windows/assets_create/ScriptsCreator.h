#pragma once

#include "windows/Explorer.h"

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

public:
	static ScriptCreator* getInstance() {
		if (s_instance == nullptr) s_instance = new ScriptCreator();
		return s_instance;
	}

	void open() { m_popen = true; }
	bool isOpen() { return m_popen == true; }

	void clearValues() {
		m_script_name[0] = '\0';
		m_script_path[0] = '\0';
	}

	void render();
};