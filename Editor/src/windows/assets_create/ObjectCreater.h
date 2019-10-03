#pragma once
#include "core/WindowManager.h"
#include "windows/Explorer.h"

class ObjectCreater
{
private:
	ObjectCreater(){}
	static ObjectCreater* s_instance;
	bool m_popen = false;
	
	// explorer path sotre switcher
	int m_path_dst_ind=0;

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
	}

	void render();

};