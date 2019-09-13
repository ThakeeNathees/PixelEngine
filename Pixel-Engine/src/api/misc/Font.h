#pragma once
#include "..//core.h"

#include "../entities/Asset.h"

namespace pe
{
	class PIXEL_ENGINE_API Font : public sf::Font, public Asset
	{
	public:
		inline Font() {
			s_font_count++;
			m_id = s_next_id++;
			m_name = std::string("font_").append(std::to_string(m_id));
		}
		inline Font(const std::string& name) : m_name(name) {
			s_font_count++;
			m_id = s_next_id++;
		}
		inline ~Font() { s_font_count--; }

		inline bool loadFromFile(const std::string& path) {
			bool success = sf::Font::loadFromFile(path);
			if (success) m_path = path;
			return success;
		}
		inline void setName(const std::string& name) override { m_name = name; }
		
		inline const std::string& getName() const override { return m_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Font; }
		inline const std::string& getPath() const { return m_path; }

	private:
		friend class FileHandler;
		static int s_font_count;
		static int s_next_id;
		std::string m_name;
		int m_id;
		std::string m_path;
	};
}