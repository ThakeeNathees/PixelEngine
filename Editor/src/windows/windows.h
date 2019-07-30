#pragma once

#include "..//widgets/widgets.h"
#include "console.h"
#include "editor_map.h"


inline void file_tree_window(std::string path)
{
	ImGui::Begin("file tree");
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	int id = 0;
	show_file_tree(path);

	ImGui::End();
}