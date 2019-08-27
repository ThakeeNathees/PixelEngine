#pragma once
#include "..//core.h"

#include "../entities/Asset.h"

namespace pe
{
	class PIXEL_ENGINE_API Font : public sf::Font, public Asset
	{
	public:
		inline Font() {
			m_id = s_font_count++;
			m_name = std::string("Font_").append(std::to_string(m_id));
		}
		inline Font(const std::string& name) : m_name(name) {
			m_id = s_font_count++;
		}

		inline bool loadFromFile(const std::string& path) {
			bool success = sf::Font::loadFromFile(path);
			if (success) m_path = path;
			return success;
		}
		inline void setName(const std::string& name) override { m_name = name; }
		
		inline const std::string& getName() const override { return m_name; }
		inline const std::string& getPath() const { return m_path; }
		inline int getId() const override { return m_id; }

	private:
		friend class AssetsReader;
		static int s_font_count;
		std::string m_name;
		int m_id;
		std::string m_path;
	};
}