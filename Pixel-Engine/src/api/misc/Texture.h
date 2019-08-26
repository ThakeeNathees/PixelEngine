#pragma once
#include "..//core.h"

namespace pe
{
	class PIXEL_ENGINE_API Texture : public sf::Texture
	{
	public:
		inline bool loadFromFile(const std::string& path, const sf::IntRect& area = sf::IntRect()) {

			bool success = sf::Texture::loadFromFile(path, area);
			if (success) m_path = path;
			return success;
		}
		inline const std::string& getPath() const { return m_path; }
	private:
		std::string m_path;
	};
}