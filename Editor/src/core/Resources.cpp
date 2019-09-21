#include "pch.h"
#include "Resources.h"

sf::Texture Resources::Icons::DIR_CLOSED;
sf::Texture Resources::Icons::DIR_OPEN;
sf::Texture Resources::Icons::FILE_TEXT;
sf::Texture Resources::Icons::FILE_PY;
sf::Texture Resources::Icons::FILE_CPP;
sf::Texture Resources::Icons::FILE_H;
sf::Texture Resources::Icons::FILE_PNG;
sf::Texture Resources::Icons::FILE_TTF;
sf::Texture Resources::Icons::FILE_BIN;


void Resources::init() {
	// TODO: add paths to conf.init
	Resources::Icons::DIR_CLOSED.loadFromFile("res/icons/dir_closed.png");
	Resources::Icons::DIR_OPEN.loadFromFile("res/icons/dir_open.png");
	Resources::Icons::FILE_TEXT.loadFromFile("res/icons/file_text.png");
	Resources::Icons::FILE_PY.loadFromFile("res/icons/file_py.png");
	Resources::Icons::FILE_CPP.loadFromFile("res/icons/file_cpp.png");
	Resources::Icons::FILE_H.loadFromFile("res/icons/file_h.png");
	Resources::Icons::FILE_PNG.loadFromFile("res/icons/file_png.png");
	Resources::Icons::FILE_TTF.loadFromFile("res/icons/file_ttf.png");
	Resources::Icons::FILE_BIN.loadFromFile("res/icons/file_bin.png");
}