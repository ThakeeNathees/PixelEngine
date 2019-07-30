#include "pch.h"

#include "editor_map.h"

std::map<std::string, EditorMap::Editor*> EditorMap::s_editor_map;
std::string EditorMap::s_last_selected_file = "";

// TODO: move these function to utils or any other file
int read_file(std::string& out, const std::string& path) {
	std::ifstream in(path);
	if (in.good())
	{
		std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		out = str;
		return 0;
	}
	return 1;
}
template <typename T>
bool is_contain(const std::map<std::string, T>& umap, std::string str ) {
	if (umap.find(str) == umap.end()) return false;
	return true;
}


// TODO: if two( or more) file have same name, different path -> set main.cpp 0, main.cpp 1 as file_name
void EditorMap::addEditor(const std::string& path) {
	Editor* editor_struct = new Editor();
	editor_struct->file_path = path;
	editor_struct->file_name = SimpleDir::get_file_name(path);
	if (SimpleDir::isEndsWith(path, ".c"))
		editor_struct->language = TextEditor::LanguageDefinition::C();
	else if (SimpleDir::isEndsWith(path, ".lua"))
		editor_struct->language = TextEditor::LanguageDefinition::Lua();
	
	editor_struct->editor.SetLanguageDefinition(editor_struct->language);
	editor_struct->editor.SetPalette(TextEditor::GetDarkPalette());
	std::string editor_string;
	int error = read_file(editor_string, path);
	if (!error)
		editor_struct->editor.SetText(editor_string);
	
	s_editor_map[path] = editor_struct;

}

void EditorMap::renderEditors()
{
	// adding new editor to map
	if ( Globals::FileTree::is_clicked_now ) {
		Globals::FileTree::is_clicked_now = false;
		s_last_selected_file = Globals::FileTree::selected_file_path;
		if (!is_contain(s_editor_map, s_last_selected_file)) {
			EditorMap::addEditor(s_last_selected_file);
		}
	}

	// rendering and removing closed
	std::vector<std::string> delete_list;
	for (auto pair : s_editor_map) {
		if (!(pair.second->p_open)) {
			delete_list.push_back(pair.first);
			continue;
		}
		ImGui::Begin(pair.second->file_name.c_str(), &(pair.second->p_open), ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		pair.second->editor.Render("text editor");
		ImGui::End();
	}

	// cleaning closed
	for (auto p : delete_list) {
		delete s_editor_map[p];
		s_editor_map.erase(p);
		if (Globals::FileTree::selected_file_path == p) {
		}
	}
}