#pragma once

#include "utils/string_util.h"
#include "console.h"

class FileTree
{
public:
	static void init();
	static void renderFileTree(const char* path);

private:
	static void fileTreeRecurtion(std::string path);
	static long long selected_file_id;
};
