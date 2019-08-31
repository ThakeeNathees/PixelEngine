#pragma once

#include "Pixel-Engine.h"

class Globals
{
public:
	Globals() = delete;
	struct FileTree {
		static std::string selected_file_path;
		static bool is_clicked_now; // set true by file tree false by WindowManager, don't touch
	};

	struct TextEditor {
		static bool is_currently_rendering_window_focus; // for focus detection of keyboard shortcuts
	};


	static pe::Assets s_assets;
	static std::string s_working_dir;
private:
};
