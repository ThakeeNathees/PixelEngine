#include "pch.h"
#include "ScenePropEditor.h"

ScenePropEditor* ScenePropEditor::s_instance = nullptr;


void ScenePropEditor::reloadScene(bool reload_file) {
	if (reload_file) m_scene_tag->attr("reload")();
	// TODO: create scene
}

void ScenePropEditor::render() {
	if (m_open) {
		ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
		ImGui::Begin("Scene Editor", &m_open);
		ImGui::End();
	}
}