#pragma once
#include "Explorer.h"
#include "pyutils/PyUtils.h"


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
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	
	ImGui::End();
}

class StartWindow
{
private:
	py::module m_conf_projupdater;
	py::object m_proj_list;
	static StartWindow* s_instance;

	// return true if any project is selected?
	bool renderProjectsList(sf::RenderWindow& window) {
		ImGui::BeginGroup();
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("ProjList", ImVec2(ImGui::GetWindowSize().x - 15, ImGui::GetWindowSize().y - ImGui::GetCursorPosY() -15 ), true);
		for (int i = 0; i < m_proj_list.attr("__len__")().cast<int>(); i++) {
			if (ImGui::Selectable( m_proj_list.attr("__getitem__")(i).attr("__getitem__")(0).cast<std::string>().c_str() , false, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(0,20))) {
				if (ImGui::IsMouseDoubleClicked(0)) {
					ImGui::EndChild();
					ImGui::PopStyleVar();
					ImGui::EndGroup();

					ImGui::End();
					ImGui::SFML::Render(window);
					CLI::chDir(m_proj_list.attr("__getitem__")(i).attr("__getitem__")(1).cast<std::string>().c_str());
					FileTree::getInstance()->reload();
					return true;
				}
			}
		}

		ImGui::EndChild();
		ImGui::PopStyleVar();
		ImGui::EndGroup();
		return false;

	}

public:
	void init() {
		try {
			m_conf_projupdater = py::module::import("conf_projupdater");
			m_proj_list = m_conf_projupdater.attr("getProjects")(CLI::getExecPath().append("/peconfig.init"));
			PE_LOG("StartWindow init success");
		}
		catch (const std::exception& e){
			PE_LOG("\nERROR: in method StartWindow::init \n%s\n", e.what());
		}

	}

	static StartWindow* getInstance() {
		if (s_instance == nullptr) s_instance = new StartWindow();
		return s_instance;
	}

	void dispStartWindow(sf::RenderWindow& window) {
		sf::Event event; sf::Clock clock;
		while (window.isOpen()) {
			// event handle
			while (window.pollEvent(event)) {
				ImGui::SFML::ProcessEvent(event);
				if (event.type == sf::Event::Closed) window.close();
			}
			ImGui::SFML::Update(window, clock.restart());
			show_dock_space();

			ImGui::Begin("Start");

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
				if (proj_name[0] == '\0' || proj_path[0]=='\0')
					ImGui::OpenPopup("Error!");
				else if (!PyUtils::getInstance()->getStrUtil().attr("isValidName")(std::string(proj_name)).cast<bool>())
					ImGui::OpenPopup("Invalid Project Name!");
				else {
					CLI::getInstance()->projInit(ExplorerPopup::getInstance()->getSelectedPath(), proj_name);
					ImGui::End();
					ImGui::SFML::Render(window);
					CLI::chDir(std::string(proj_path).append("/").append(proj_name));
					m_conf_projupdater.attr("insertNewProj")(proj_name, std::string(proj_path).append("/").append(proj_name), CLI::getExecPath().append("/peconfig.init"));
					FileTree::getInstance()->reload();
					return;
				}
			}

			// older project list
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
			ImGui::Separator();

			ImGui::Text("Open Project"); ImGui::Text("");
			if (renderProjectsList(window)) return;

			// popups render
			if (ImGui::BeginPopupModal("Error!")) {
				ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
				ImGui::Image(Resources::OtherIcons::_ERROR); ImGui::SameLine();
				if (proj_name[0] == '\0') ImGui::Text("Error! enter a Project Name!");
				else ImGui::Text("Error! enter the Project Path!");
				if (ImGui::Button("OK",ImVec2(280, 20))) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			if (ImGui::BeginPopupModal("Invalid Project Name!")) {
				ImGui::SetWindowSize(ImVec2(300, 140), ImGuiCond_Once);
				ImGui::Image(Resources::OtherIcons::_ERROR); ImGui::SameLine();
				ImGui::TextWrapped("Error! project name is invalid. (project name must start with alphabatic character and doesn't contain any of the following \\ / : * ? \" < > | spacebar)");
				if (ImGui::Button("OK", ImVec2(280, 20))) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}


			ExplorerPopup::getInstance()->render();

			if (ExplorerPopup::getInstance()->isPathSelected()) {
				const char* c = ExplorerPopup::getInstance()->getSelectedPath().c_str();
				int i = 0;
				while (c[i]) {
					proj_path[i] = c[i++];
				}
				proj_path[i] = 0;
				ExplorerPopup::getInstance()->setPathSelectedFalse();
			}
			ImGui::End();


			ImGui::SFML::Render(window);
			window.display();

		}
	}

};