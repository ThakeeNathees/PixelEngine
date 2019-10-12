#pragma once
#include "core/PyUtils.h"
#include "windows/ExplorerPopup.h"
#include "ScriptsCreator.h"

class ObjectCreater
{
private:
	ObjectCreater(){
		m_py_objmaker = py::module::import("obj_maker");
	}

	static ObjectCreater* s_instance;
	//pe::Object* m_object;
	py::module m_py_objmaker;


	bool m_popen = false;
	char m_obj_name[1024] = {};
	char m_obj_path[1024] = {};
	char m_script_path[1024] = {};
	char m_script_name[1024] = {};

	std::string m_class_path;
	pe::Object::ObjectType m_pe_obj_type;

	int m_obj_type = 0; // 0: unknown, 1:python, 2:cpp
	int m_z_index = 0;
	int m_visible = 1; // int for combo
	int m_persistance = 0;
	
	// explorer path sotre switcher
	int m_path_dst_ind=0; // 0 - obj path, 1 - script path

public:
	static ObjectCreater* getInstance() {
		if (s_instance == nullptr) s_instance = new ObjectCreater();
		return s_instance;
	}

	void open() { m_popen = true; }
	bool isOpen() { return m_popen == true; }

	// clear values before appearing again
	void clearValues(){
		ExplorerPopup::getInstance()->setPath(CLI::getCwd());
		m_obj_name[0]		= '\0';
		m_obj_path[0]		= '\0';
		m_script_path[0]	= '\0';
		m_script_name[0]		= '\0';

		m_obj_type		= 0;
		m_z_index		= 0;
		m_visible		= 1;
		m_persistance	= 0;
	}

	void render();

};