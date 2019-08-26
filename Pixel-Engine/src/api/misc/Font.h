#pragma once
#include "..//core.h"


namespace pe
{
	class PIXEL_ENGINE_API Font : public sf::Font
	{
	public:
		inline bool loadFromFile(const std::string& path) {
			bool success = sf::Font::loadFromFile(path);
			if (success) m_path = path;
			return success;
		}
		
		inline const std::string& getPath() const { return m_path; }

	private:
		std::string m_path;
	};
}