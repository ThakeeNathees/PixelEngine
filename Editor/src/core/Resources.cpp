#include "pch.h"
#include "Resources.h"


std::map<std::string, sf::Texture> Resources::s_file_format_icons;
std::map<std::string, sf::Texture> Resources::s_menu_icons;
std::map<std::string, sf::Texture> Resources::s_other_icons;
std::map<std::string, Resources::FontData> Resources::s_fonts;

sf::Texture Resources::LOGO;
sf::Texture Resources::LOGO_PE;
sf::Texture Resources::PNG_BG;
sf::Sprite Resources::PNG_BG_SPRITE;
