#include "pch.h"
#include "Resources.h"
#include "cli/CLI.h"
#include "../pyutils/PyUtils.h"


pe::_peproj Resources::s_proj;

sf::Texture Resources::LOGO;

sf::Texture Resources::FileFormatIcons::DIR_CLOSED;
sf::Texture Resources::FileFormatIcons::DIR_OPEN;
sf::Texture Resources::FileFormatIcons::_FILE_UNKNOWN;
sf::Texture Resources::FileFormatIcons::FILE_PEPROJ;
sf::Texture Resources::FileFormatIcons::FILE_TEXT;
sf::Texture Resources::FileFormatIcons::FILE_XML;
sf::Texture Resources::FileFormatIcons::FILE_PY;
sf::Texture Resources::FileFormatIcons::FILE_PYC;
sf::Texture Resources::FileFormatIcons::FILE_CPP;
sf::Texture Resources::FileFormatIcons::FILE_H;
sf::Texture Resources::FileFormatIcons::FILE_HPP;
sf::Texture Resources::FileFormatIcons::FILE_PNG;
sf::Texture Resources::FileFormatIcons::FILE_TTF;
sf::Texture Resources::FileFormatIcons::FILE_BIN;
sf::Texture Resources::FileFormatIcons::FILE_DLL;
sf::Texture Resources::FileFormatIcons::FILE_OBJ;

sf::Texture Resources::MenuIcons::NONE;
sf::Texture Resources::MenuIcons::RENAME;
sf::Texture Resources::MenuIcons::_DELETE;
sf::Texture Resources::MenuIcons::OPEN_IN_EXPLORER;
sf::Texture Resources::MenuIcons::NEW_OBJ;

sf::Texture Resources::OtherIcons::_ERROR;
sf::Texture Resources::OtherIcons::WARNING;
sf::Texture Resources::OtherIcons::EXPLORER_UP;
sf::Texture Resources::OtherIcons::EXPLORER_REFRESH;

ImFont* Resources::Fonts::PROGRAMMING=nullptr;

// TODO: log everything
/* this will find and read the proj file and load the assets */
int Resources::readProjFile() {

	CLI::getInstance()->projUpdate(false);

	std::string proj_file_name = PyUtils::getInstance()->getFileUtil().attr("getProjFileName")().cast<std::string>();
	if (proj_file_name == std::string("")) { 
		PE_LOG("\nERROR: in method Resources::readProjFile : can't find project file (*.peproj)\n");
		return 1; 
	} else PE_LOG("project file found : %s", proj_file_name.c_str());

	pe::FileHandler file_handler;
	int error = file_handler.readProject(proj_file_name.c_str());
	if (error) { 
		PE_LOG("\nERROR: in method Resources::readProjFile : file_handler.readProj(%s)\n", proj_file_name.c_str());
		return 1; 
	} else PE_LOG("project file read success");

	s_proj = file_handler.getProject();
	error = file_handler.readAssets( s_proj.assets_path.c_str() );
	if (error) { 
		PE_LOG("\nERROR: in method Resources::readProjFile : file_handler.readAssets(%s)\n", s_proj.assets_path.c_str());
		return 1; 
	} else PE_LOG("assets file read success");

	PE_LOG("objects reading begin (%s objects)", s_proj.objects_path.size());
	for (auto& path : s_proj.objects_path) {
		file_handler.readObject(path.c_str(), nullptr);
		PE_LOG("\tobject read success : %s", path.c_str());
	}
	PE_LOG("scene reading begin (%s scenes)", s_proj.scene_paths.size());
	for (auto& path : s_proj.scene_paths) {
		file_handler.readScenes(path.c_str(), nullptr);
		PE_LOG("\tscene read success : %s", path.c_str());
	}
	PE_LOG("\n");
}