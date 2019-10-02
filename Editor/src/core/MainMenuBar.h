#pragma once

#include "Resources.h"

class MainMenuBar
{
private:
	static MainMenuBar* s_instance;
	bool m_is_openpopup_exitconform = false;

public:
	static MainMenuBar* getInstance() { 
		if (s_instance == nullptr) s_instance = new MainMenuBar();
		return s_instance;
	}

	void render(){
		renderMenuBar();
		renderPopups();
	}


private:
	void renderMenuBar() {
		if (ImGui::BeginMainMenuBar())
		{

			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) {
					m_is_openpopup_exitconform = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}
	void renderPopups() {
		// open popups
		if (m_is_openpopup_exitconform) {
			ImGui::OpenPopup("Exit Conformation");
			m_is_openpopup_exitconform = false;
		}

		// render popups
		if (ImGui::BeginPopupModal("Exit Conformation")) {
			static ImVec2 size = ImVec2(220,120);
			ImGui::SetWindowSize(size, ImGuiCond_Once);
			ImGui::Image(Resources::OtherIcons::WARNING); ImGui::SameLine();
			ImGui::Text("Are you sure?");
			if (ImGui::Button("Yes", ImVec2(90, 20)) ) { ImGui::CloseCurrentPopup(); } // TODO: exit the programme
			ImGui::SameLine();
			if (ImGui::Button("No", ImVec2(90, 20) )) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}
	}
};