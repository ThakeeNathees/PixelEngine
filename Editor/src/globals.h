#pragma once


class Globals
{
public:
	struct FileTree {
		static std::string selected_file_path;
		static bool is_clicked_now; // set true by file tree false by EditorMap, don't touch
	};

	struct TextEditor {
		static bool is_currently_rendering_window_focus; // for focus detection of keyboard shortcuts
	};


private:
	inline Globals() {}
	static std::shared_ptr<Globals> m_globals;
};
