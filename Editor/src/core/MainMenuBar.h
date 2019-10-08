#pragma once

#include "core/cli/CLI.h"
#include "Resources.h"
#include "WindowManager.h"
#include "core/ApplicationHolder.h"

#include "windows/assets_create/ObjectCreator.h"
#include "windows/assets_create/ScriptsCreator.h"

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
			renderFileMenu();
			renderEditMenu();
			renderCreateMenu();
			renderDebugMenu();
			
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
			ImGui::Image(Resources::getOtherIcon("warning")); ImGui::SameLine();
			ImGui::Text("Are you sure?");
			if (ImGui::Button("Yes", ImVec2(90, 20)) ) { ImGui::CloseCurrentPopup(); } // TODO: exit the programme
			ImGui::SameLine();
			if (ImGui::Button("No", ImVec2(90, 20) )) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}
	}

	// render menus
	void renderFileMenu() {
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit")) {
				m_is_openpopup_exitconform = true;
			}
			ImGui::EndMenu();
		}
	}

	void renderEditMenu() {
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
	}

	void renderCreateMenu() {
		if (ImGui::BeginMenu("Create"))
		{
			ImGui::Image(Resources::getMenuIcon("new_object")); ImGui::SameLine();
			if (ImGui::MenuItem("New Object")) {
				if (!ObjectCreater::getInstance()->isOpen()) {
					ObjectCreater::getInstance()->clearValues();
					ObjectCreater::getInstance()->open();
				}
			}

			ImGui::Image(Resources::getMenuIcon("new_script")); ImGui::SameLine();
			if (ImGui::MenuItem("New Script")) {
				if (!ScriptCreator::getInstance()->isOpen()) {
					ScriptCreator::getInstance()->clearValues();
					ScriptCreator::getInstance()->open();
				}
			}

			ImGui::EndMenu();
		}
	}

	void renderDebugMenu() {
		if (ImGui::BeginMenu("Debug")) {
			if (ImGui::MenuItem("Debug Mode", NULL, ApplicationHolder::s_debug_mode )) {}
			if (ImGui::MenuItem("Reload Scripts")) { ApplicationHolder::reloadScripts(); }
			if (ImGui::MenuItem("Reload On Save",NULL, &ApplicationHolder::s_reload_on_save)){}
			if (ImGui::MenuItem("Reload Project")) { 
				CLI::getInstance()->projUpdate(false);
				ApplicationHolder::reloadApplication(); 
			}
			ImGui::EndMenu();
		}
	}
};