#pragma once

#include "..//utils/string_util.h"

#include "console.h"
#include "editor_map.h"
#include "file_tree.h"
#include "render_window.h"
#include "image_viwer.h"
#include "assets_window.h"
#include "property_window/proprty_editor.h"



class WindowManager
{
public:
	WindowManager() = delete;
	inline static void windowSignalFromFileTree()
	{
		if (Globals::FileTree::is_clicked_now) {
			Globals::FileTree::is_clicked_now = false;
			std::string path = Globals::FileTree::selected_file_path;
			if (utils::isPathImage(path)){
				ImageViwer::setImage(path.c_str());
			}
			else 
				EditorMap::addEditor( path );
		}
	}


	inline static void show_dock_space()
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
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		ImGui::PopStyleVar(3);

		ImGuiIO& io = ImGui::GetIO();
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		ImGui::End();

	}

private:
	
};

