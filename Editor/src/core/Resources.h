#pragma once

#include "pch.h"

class Resources
{
public:


	// textures
	static sf::Texture LOGO;
	static sf::Texture LOGO_PE;
	static sf::Texture PNG_BG;

	static int readProjFile();

	static sf::Texture& getFileFormatIcon(const std::string& name) {
		assert( s_file_format_icons.find(name) != s_file_format_icons.end() && name.c_str() );
		return s_file_format_icons[name];
	}
	static sf::Texture& getMenuIcon(const std::string& name) {
		assert(s_menu_icons.find(name) != s_menu_icons.end() && name.c_str() );
		return s_menu_icons[name];
	}
	static sf::Texture& getOtherIcon(const std::string& name) {
		assert(s_other_icons.find(name) != s_other_icons.end() && name.c_str() );
		return s_other_icons[name];
	}
	static ImFont* getFont(const std::string& name) {
		assert(s_fonts.find(name) != s_fonts.end() && name.c_str());
		return s_fonts[name];
	}


	static void addFileFormatIcon(const std::string& name, const sf::Texture& tex) {
		s_file_format_icons[name] = tex;
	}
	static void addMenuIcon(const std::string& name, const sf::Texture& tex) {
		s_menu_icons[name] = tex;
	}
	static void addOtherIcon(const std::string& name, const sf::Texture& tex) {
		s_other_icons[name] = tex;
	}
	static void addFont(const std::string& name, ImFont* font) {
		s_fonts[name] = font;
	}
	

private:
	Resources() {}
	static std::map<std::string, sf::Texture> s_file_format_icons;
	static std::map<std::string, sf::Texture> s_menu_icons;
	static std::map<std::string, sf::Texture> s_other_icons;
	static std::map<std::string, ImFont*> s_fonts;

	
};