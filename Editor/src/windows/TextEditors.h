#pragma once

#include "..//core/cli/CLI.h"

/* class to hold all text editors */
class TextEditors
{
public:
	struct TextEditorData {

		TextEditorData(const std::string& _title="__default_text_editor", const std::string& _path="", long long _id=-1, const TextEditor::LanguageDefinition& _lang= TextEditor::LanguageDefinition::Python()) {
			title = _title;
			path = _path;
			id = _id;

			editor.SetLanguageDefinition(_lang);
			std::string text;
			if (!CLI::readTextFile(text, path)) { // TODO: error handle
				editor.SetText(text);
			}
		}
		std::string path;
		bool p_open = true;
		bool rendering = false; // combine with p_open to ask are you sure, TODO:
		std::string title;
		long long id;
		TextEditor editor;
	};

	static void addTextEditor(const std::string& title, const std::string& path, long long id, const TextEditor::LanguageDefinition& _lang = TextEditor::LanguageDefinition::Python()) {
		s_text_editors[id] = new TextEditorData(title, path, id, _lang);
	}

	static void renderEditors() {
		for (auto pair : s_text_editors) {
			if (pair.second->p_open) {
				ImGui::Begin(pair.second->title.c_str(), &pair.second->p_open, ImGuiWindowFlags_MenuBar);
				ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
				pair.second->editor.Render(pair.second->title.c_str());
				ImGui::End();
			}
		}
	}

private:
	static std::map<long long, TextEditorData*> s_text_editors;
	TextEditors() {}
};