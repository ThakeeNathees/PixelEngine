#pragma once


class FileTree
{
public:
	
	static void renderFileTree(const char* path);

private:
	static void fileTreeRecurtion(std::string path);
	static long long selected_file_id;
};
