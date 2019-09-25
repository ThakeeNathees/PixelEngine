#pragma once

#include "pch.h"

class Popups
{
public:
	class PopupData
	{
	public:
		std::string path;
		bool is_path_dir;
	};


private:
	static Popups* s_popups; // for python modules
	static std::vector<std::string> s_open_list;
	static std::map <std::string, PopupData > s_popup_data;
	static void renderDeleteConform();

public:
	

	static void openPopup(const std::string& title, const PopupData& data) {
		PopupData daat;
		s_open_list.push_back(title);
		s_popup_data[title] = data;
	}


	static void render() {

		for (auto title : s_open_list) {
			ImGui::OpenPopup(title.c_str());
		}
		s_open_list.clear();

		// rendering
		renderDeleteConform();
	}
};