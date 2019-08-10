#include "pch.h"

#include <SFML/Window.hpp> // for keyboard shortcut : TODO: make indipendent of sfml here
#include "editor_map.h"

// initialize member fields
std::map<std::string, EditorMap::Editor*> EditorMap::s_editor_map;
std::string EditorMap::s_last_selected_file = "";

// forward declaration
void render_menubar(EditorMap::Editor* editor_struct);
void keyboard_shortcut(EditorMap::Editor* editor_struct);

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
	if (is_contain(s_editor_map, s_last_selected_file))
		return;

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
	// rendering and removing closed
	std::vector<std::string> delete_list;
	for (auto pair : s_editor_map) {
		if (!(pair.second->p_open)) {
			delete_list.push_back(pair.first);
			continue;
		}
		ImGui::Begin(pair.second->file_name.c_str(), &(pair.second->p_open), ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		render_menubar(pair.second);
		pair.second->editor.Render("text editor");
		keyboard_shortcut(pair.second); // call this after editor.render -> globals::Texteditor::is_focus assigned above
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

///////////////// functions
void save(std::string text_to_save, const char* file_path)
{
	std::ofstream save_file;
	save_file.open(file_path);
	save_file << text_to_save;
	save_file.close();
}

void keyboard_shortcut(EditorMap::Editor* editor_struct)
{
	TextEditor& editor = editor_struct->editor;
	ImGuiIO& io = ImGui::GetIO();
	auto shift = io.KeyShift;
	auto ctrl = io.ConfigMacOSXBehaviors ? io.KeySuper : io.KeyCtrl;
	auto alt = io.ConfigMacOSXBehaviors ? io.KeyCtrl : io.KeyAlt;

	if ( Globals::TextEditor::is_currently_rendering_window_focus ) {
		if (!editor.IsReadOnly() && ctrl && !shift && !alt && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			save(editor.GetText(), editor_struct->file_path.c_str());
		}
	}

}

void render_menubar(EditorMap::Editor* editor_struct)
{
	TextEditor& editor = editor_struct->editor;
	auto cpos = editor.GetCursorPosition();
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save", "Ctrl-S"))
			{
				auto text_to_save = editor.GetText();
				save(text_to_save, editor_struct->file_path.c_str());

			}
			if (ImGui::MenuItem("Quit"))
				editor_struct->p_open = false;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			bool ro = editor.IsReadOnly();
			if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
				editor.SetReadOnly(ro);
			ImGui::Separator();

			if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
				editor.Undo();
			if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
				editor.Redo();

			ImGui::Separator();

			if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
				editor.Copy();
			if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
				editor.Cut();
			if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
				editor.Delete();
			if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
				editor.Paste();

			ImGui::Separator();

			if (ImGui::MenuItem("Select all", nullptr, nullptr))
				editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Dark palette"))
				editor.SetPalette(TextEditor::GetDarkPalette());
			if (ImGui::MenuItem("Light palette"))
				editor.SetPalette(TextEditor::GetLightPalette());
			if (ImGui::MenuItem("Retro blue palette"))
				editor.SetPalette(TextEditor::GetRetroBluePalette());
			
			ImGui::Separator();
			if (ImGui::MenuItem("AngelScript"))
				editor.SetLanguageDefinition(TextEditor::LanguageDefinition::AngelScript());
			if (ImGui::MenuItem("C"))
				editor.SetLanguageDefinition( TextEditor::LanguageDefinition::C() );
			if (ImGui::MenuItem("C++"))
				editor.SetLanguageDefinition( TextEditor::LanguageDefinition::CPlusPlus() );
			if (ImGui::MenuItem("GLSL"))
				editor.SetLanguageDefinition( TextEditor::LanguageDefinition::GLSL() );
			if (ImGui::MenuItem("HLSL"))
				editor.SetLanguageDefinition( TextEditor::LanguageDefinition::HLSL() );
			if (ImGui::MenuItem("Lua"))
				editor.SetLanguageDefinition( TextEditor::LanguageDefinition::Lua() );
			if (ImGui::MenuItem("SQL"))
				editor.SetLanguageDefinition( TextEditor::LanguageDefinition::SQL() );
			// TODO: add plan text here
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
		editor.IsOverwrite() ? "Ovr" : "Ins",
		editor.CanUndo() ? "*" : " ",
		editor.GetLanguageDefinition().mName.c_str(), editor_struct->file_name.c_str() );
}