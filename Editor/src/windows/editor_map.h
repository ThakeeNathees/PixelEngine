#pragma once

#include "simpledir.h"
#include "TextEditor.h"
#include "globals.h"

class EditorMap
{
public:
	struct Editor
	{
		TextEditor editor;
		bool p_open = true;
		std::string file_path;
		std::string file_name;
		TextEditor::LanguageDefinition language = TextEditor::LanguageDefinition::CPlusPlus();
	};

	static void addEditor(const std::string& path);
	static void renderEditors();
	

private:
	static std::string s_last_selected_file;
	static std::map<std::string, Editor*> s_editor_map; // path, editor

};