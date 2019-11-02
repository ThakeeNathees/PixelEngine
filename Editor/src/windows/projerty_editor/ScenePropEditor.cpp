#include "pch.h"
#include "ScenePropEditor.h"

ScenePropEditor* ScenePropEditor::s_instance = nullptr;

void ScenePropEditor::render() {
	if (m_open) {
		ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
		ImGui::Begin("Scene Editor", &m_open);
		ImGui::End();
	}
}