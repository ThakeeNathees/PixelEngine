#pragma once

#include "..//utils/string_util.h"

#include "..//widgets/widgets.h"
#include "console.h"
#include "editor_map.h"
#include "file_tree.h"
#include "render_window.h"
#include "image_viwer.h"
#include "property_window/proprty_editor.h"


// adding new editor to map
class WindowManager
{
public:
	inline static void windowSignalFromFileTree()
	{
		if (Globals::FileTree::is_clicked_now) {
			Globals::FileTree::is_clicked_now = false;
			std::string path = Globals::FileTree::selected_file_path;
			if (utils::isPathImage(path)){
				ImageViwer::setImage(path.c_str());
			}
			else 
				EditorMap::addEditor( path );
		}
	}

private:
	
};

