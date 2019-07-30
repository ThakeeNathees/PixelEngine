#pragma once


class Globals
{
public:
	struct FileTree {
		static std::string selected_file_path;
		static bool is_clicked_now; // set true by file tree false by EditorMap
	};

private:
	inline Globals() {}
	static std::shared_ptr<Globals> m_globals;
};
