#include "pch.h"
#include "file_tree.h"

#include "simpledir.h"
#include "..//globals.h"

void FileTree::renderFileTree(const char* path)
{
	ImGui::Begin("file tree");
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	int id = 0;
	fileTreeRecurtion(path);
	ImGui::End();
}


void FileTree::fileTreeRecurtion(std::string path) {
	long long id = simple_hash(path.substr(max((int)path.length() - 64, 0))); // last 64 character of the path
	static long long selected_id = -1;

	if (SimpleDir::isDirectory(path)) {
		if (ImGui::TreeNode((path == ".") ? "files" : SimpleDir::get_file_name(path).c_str())) {
			SimpleDir dir;
			dir.open(path);
			for (std::string p : dir.getFiles()) {
				fileTreeRecurtion(p);
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



// TODO: fix this code and update file tree recurtion
/*
void FileTree::updateDir(Folder* folder) // store the file tree in a data structure
{
	SimpleDir dir;
	dir.open(std::string(folder->path));
	for (std::string path : dir.getFiles())
	{
		if (SimpleDir::isDirectory(path)) {
			Folder* sub_folder = new Folder( path.c_str() );
			updateDir(sub_folder);
			folder->folders.push_back(sub_folder);
		}
		else {
			folder->files.push_back(path.c_str());
		}

	}
}
*/

// backup
/*

void FileTree::fileTreeRecurtion(std::string path) {
	long long id = simple_hash(path.substr(max((int)path.length() - 64, 0))); // last 64 character of the path
	static long long selected_id = -1;

	if (SimpleDir::isDirectory(path)) {
		if (ImGui::TreeNode((path == ".") ? "files" : SimpleDir::get_file_name(path).c_str())) {
			SimpleDir dir;
			dir.open(path);
			for (std::string p : dir.getFiles()) {
				fileTreeRecurtion(p);
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
*/