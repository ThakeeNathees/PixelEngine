#pragma once

namespace pe
{
	inline std::vector<std::string> split(const std::string& s, char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	// replace dst to src in string str
	inline std::string __removeWiteSpace(std::string str) {
		std::size_t pos = -1;
		std::string ret;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] != ' ' && str[i] != '\t')
				ret += str[i];
		}
		return ret;
	}

	// convert C:\dev\engine -> C:/dev/engine
	inline std::string __fixPath(const std::string& path) {
		std::size_t pos = -1;
		std::string ret;
		for (int i = 0; i < path.size(); i++) {
			if (path[i] == '\\') ret += '/';
			else ret += path[i];
		}
		return ret;
	}


	// init file functions //

	/* convert "str_value" -> str_value  (remove the quouts in the string and return the string, need for init file read)*/
	inline std::string __getValueString(const std::string& str) { // TODO: error handle
		std::size_t pos0 = str.find('"', 0);
		std::size_t pos1 = str.find('"', pos0+1);
		if (pos0 == std::string::npos || pos1 == std::string::npos) {
			return str;
		}

		return str.substr(pos0+1, pos1 - pos0-1);
	}

	// convert "F1", "F2", ... to sf function key
	inline sf::Keyboard::Key __getFunctionKey(const std::string& str) {
		if (str == std::string("F1")) return sf::Keyboard::F1;
		else if (str == std::string("F1")) return sf::Keyboard::F1;
		else if (str == std::string("F2")) return sf::Keyboard::F2;
		else if (str == std::string("F3")) return sf::Keyboard::F3;
		else if (str == std::string("F4")) return sf::Keyboard::F4;
		else if (str == std::string("F5")) return sf::Keyboard::F5;
		else if (str == std::string("F6")) return sf::Keyboard::F6;
		else if (str == std::string("F7")) return sf::Keyboard::F7;
		else if (str == std::string("F8")) return sf::Keyboard::F8;
		else if (str == std::string("F9")) return sf::Keyboard::F9;
		else if (str == std::string("F10")) return sf::Keyboard::F10;
		else if (str == std::string("F11")) return sf::Keyboard::F11;
		return sf::Keyboard::Unknown;
	}
}