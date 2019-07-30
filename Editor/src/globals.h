#pragma once

#include <memory>

class Globals
{
public:
	struct FileTree {
		static std::string selected_file_path;
	};

private:
	inline Globals() {}
	static std::shared_ptr<Globals> m_globals;
};
