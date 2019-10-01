#include "pch.h"
#include "Resources.h"

sf::Texture Resources::LOGO;

// texture's load from file in CLI::init()
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

sf::Texture Resources::OtherIcons::WARNING;
sf::Texture Resources::OtherIcons::EXPLORER_UP;
sf::Texture Resources::OtherIcons::EXPLORER_REFRESH;

ImFont* Resources::Fonts::PROGRAMMING=nullptr;