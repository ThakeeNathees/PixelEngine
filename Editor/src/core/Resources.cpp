#include "pch.h"
#include "Resources.h"
#include "cli/CLI.h"
#include "../pyutils/PyUtils.h"


/****** applicaton holder static declarations ********/
#include "ApplicationHolder.h"
bool ApplicationHolder::s_is_running = false;
bool ApplicationHolder::s_has_error = false;
bool ApplicationHolder::s_is_focus = false;
bool ApplicationHolder::__s_is_application_reloaded = false;
bool ApplicationHolder::s_reload_on_save = true;
bool* ApplicationHolder::s_debug_mode = nullptr;

std::string ApplicationHolder::s_proj_file_name;
pe::Application* ApplicationHolder::s_application;
sf::RenderTexture ApplicationHolder::s_render_texture;
sf::Vector2f ApplicationHolder::s_mouse_pos;
sf::Vector2f ApplicationHolder::s_mouse_rel_pos;

/*********************************************/

std::map<std::string, sf::Texture> Resources::s_file_format_icons;
std::map<std::string, sf::Texture> Resources::s_menu_icons;
std::map<std::string, sf::Texture> Resources::s_other_icons;
std::map<std::string, ImFont*> Resources::s_fonts;

sf::Texture Resources::LOGO;

// TODO: log everything
/* this will find and read the proj file and load the assets */
int Resources::readProjFile() {

	CLI::getInstance()->projUpdate(false);

	std::string proj_file_name = PyUtils::getInstance()->getFileUtil().attr("getProjFileName")().cast<std::string>();
	if (proj_file_name == std::string("")) { 
		PE_LOG("\nERROR: in method Resources::readProjFile : can't find project file (*.peproj)\n");
		return 1; 
	} else PE_LOG("project file found : %s", proj_file_name.c_str());

	ApplicationHolder::setProjFileName(proj_file_name);
	ApplicationHolder::start();
}