#pragma once
#include "Explorer.h"

// TODO: move this
inline void show_dock_space()
{
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	bool p_open = false;
	ImGui::Begin("DockSpace", &p_open, window_flags);
	ImGui::PopStyleVar(3);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	ImGui::End();

}

class StartWindow
{
private:
	static StartWindow* s_instance;

	void renderProjectsList() {
		ImGui::BeginGroup();
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		
		ImGui::BeginChild("ProjList", ImVec2(ImGui::GetWindowSize().x - 15, ImGui::GetWindowSize().y - ImGui::GetCursorPosY() -15 ), true);
		for (int i = 0; i < 10; i++) {
			break;
			ImGui::Text(std::to_string(i).c_str());
		}
		ImGui::EndChild();

		ImGui::PopStyleVar();
		ImGui::EndGroup();
		
	}

public:
	static StartWindow* getInstance() {
		if (s_instance == nullptr) s_instance = new StartWindow();
		return s_instance;
	}

	void dispStartWindow(sf::RenderWindow& window) {
		ExplorerPopup explorer("C:/");
		sf::Event event; sf::Clock clock;
		while (window.isOpen()) {
			// event handle
			while (window.pollEvent(event)) {
				ImGui::SFML::ProcessEvent(event);
				if (event.type == sf::Event::Closed) window.close();
				if (event.type == sf::Event::GainedFocus) { FileTree::getInstance()->reload(); }
			}
			ImGui::SFML::Update(window, clock.restart());
			show_dock_space();

			ImGui::Begin("Start");
			ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

			// start title
			ImGui::Text("Create a new project Here"); ImGui::Text("");

			// start body
			static char proj_name[1024];
			ImGui::InputText("proj_name", proj_name, sizeof(proj_name));

			static char proj_path[1024];
			ImGui::InputText("proj_path", proj_path, sizeof(proj_path));
			ImGui::SameLine();
			if (ImGui::ImageButton(Resources::FileFormatIcons::DIR_OPEN)) {
				ImGui::OpenPopup("Explorer");
			}

			if (ImGui::Button("Create")) {
				if (proj_name[0] == '\0' || proj_path[0]=='\0') ImGui::OpenPopup("Error!");
				else {
					CLI::getInstance()->projInit(explorer.getSelectedPath(), proj_name);
					ImGui::End();
					ImGui::SFML::Render(window);
					CLI::chDir(std::string(proj_path).append("/").append(proj_name));
					FileTree::getInstance()->reload();
					return;
				}
			}

			// older project list
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
			ImGui::Separator();

			ImGui::Text("Open Project"); ImGui::Text("");
			renderProjectsList();


			if (ImGui::BeginPopupModal("Error!")) {
				if (proj_name[0] == '\0') ImGui::Text("Error! enter a Project Name!");
				else ImGui::Text("Error! enter the Project Path!");
				if (ImGui::Button("OK")) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}


			explorer.render();

			if (explorer.isPathSelected()) {
				const char* c = explorer.getSelectedPath().c_str();
				int i = 0;
				while (c[i]) {
					proj_path[i] = c[i++];
				}
				proj_path[i] = 0;
			}
			ImGui::End();


			ImGui::SFML::Render(window);
			window.display();

		}
	}

};