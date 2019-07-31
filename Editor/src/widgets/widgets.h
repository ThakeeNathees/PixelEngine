#pragma once

#include "simpledir.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include "..//globals.h"



inline void show_dock_space()
{
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	bool p_open = false;
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	ImGui::PopStyleVar(3);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	ImGui::End();

}

inline void show_file_tree(std::string path) {
	long long id = simple_hash( path.substr(max((int)path.length() - 64, 0))   ); // last 64 character of the path
	static long long selected_id = -1;

	if (SimpleDir::isDirectory(path)) {
		if (ImGui::TreeNode((path == ".") ? "files" : SimpleDir::get_file_name(path).c_str())) {
			SimpleDir dir;
			dir.open(path);
			for (std::string p : dir.getFiles()) {
				show_file_tree(p);
			}
			ImGui::TreePop();
		}
	}
	else
	{
		ImGuiTreeNodeFlags node_flags = 0;
		if (selected_id == id) node_flags |= ImGuiTreeNodeFlags_Selected;
		node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

		//ImGui::PushStyleColor(0, { 255,0,0,255 });
		//if ( SimpleDir::isEndsWith(path, ".cpp") || SimpleDir::isEndsWith(path, ".h"))
		ImGui::TreeNodeEx((void*)(intptr_t)(id), node_flags, SimpleDir::get_file_name(path).c_str());
		//ImGui::PopStyleColor();
		if (ImGui::IsItemClicked()) {
			selected_id = id;
			Globals::FileTree::is_clicked_now = true;
			Globals::FileTree::selected_file_path = path;
		}

	}

}

