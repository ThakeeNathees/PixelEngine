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
		bool saved = true; // file.py* -> file.py
		bool rendering = false; // combine with p_open to ask are you sure, TODO:
		std::string title;
		long long id;
		TextEditor editor;
	};

	static void openTextEditor(const std::string& title, const std::string& path, long long id, const TextEditor::LanguageDefinition& _lang = TextEditor::LanguageDefinition::Python()) {
		if (s_text_editors.find(id) == s_text_editors.end())
			s_text_editors[id] = new TextEditorData(title, path, id, _lang);
		else s_text_editors[id]->p_open = true;
	}

	static void renderEditors() {
		for (auto pair : s_text_editors) {
			if (pair.second->p_open) {
				ImGui::Begin(pair.second->title.c_str(), &pair.second->p_open, ImGuiWindowFlags_MenuBar);
				ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
				handleShortcuts(pair.second);
				renderMenubar(pair.second);
				pair.second->editor.Render(pair.second->title.c_str());
				ImGui::End();
			}
		}
	}

private:
	static std::map<long long, TextEditorData*> s_text_editors;
	TextEditors() {}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	static void handleShortcuts(TextEditorData* data)
	{
		TextEditor& editor = data->editor;
		ImGuiIO& io = ImGui::GetIO();
		auto shift = io.KeyShift;
		auto ctrl = io.ConfigMacOSXBehaviors ? io.KeySuper : io.KeyCtrl;
		auto alt = io.ConfigMacOSXBehaviors ? io.KeyCtrl : io.KeyAlt;

		if (data->editor.isFocus()) {
			// Ctrl+s : save
			if (!editor.IsReadOnly() && ctrl && !shift && !alt && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				data->saved = true;
				CLI::save(editor.GetText(), data->path);
			}
		}

	}

	static void renderMenubar(TextEditorData* data)
	{
		TextEditor& editor = data->editor;
		auto cpos = editor.GetCursorPosition();
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save", "Ctrl-S"))
				{
					auto text_to_save = editor.GetText();
					CLI::save(text_to_save, data->path);
					data->saved = true;

				}
				if (ImGui::MenuItem("Quit"))
					data->p_open = false;
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
					editor.SetLanguageDefinition(TextEditor::LanguageDefinition::C());
				if (ImGui::MenuItem("C++"))
					editor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
				if (ImGui::MenuItem("GLSL"))
					editor.SetLanguageDefinition(TextEditor::LanguageDefinition::GLSL());
				if (ImGui::MenuItem("HLSL"))
					editor.SetLanguageDefinition(TextEditor::LanguageDefinition::HLSL());
				if (ImGui::MenuItem("Lua"))
					editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
				if (ImGui::MenuItem("SQL"))
					editor.SetLanguageDefinition(TextEditor::LanguageDefinition::SQL());
				if (ImGui::MenuItem("Python"))
					editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Python());
				if (ImGui::MenuItem("PlainText"))
					editor.SetLanguageDefinition(TextEditor::LanguageDefinition::PlainText());
				// TODO: add plan text here
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if (data->editor.IsTextChanged()) data->saved = false;
		ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s%s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
			editor.IsOverwrite() ? "Ovr" : "Ins",
			data->editor.IsReadOnly() ? "read_only" : "read_write",
			editor.GetLanguageDefinition().mName.c_str(),
			data->title.c_str(), data->saved ? "" : "*"
		);
	}

};