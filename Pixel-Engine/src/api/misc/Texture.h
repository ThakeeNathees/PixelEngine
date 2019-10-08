#pragma once
#include "..//core.h"

#include "..//entities/Asset.h"

namespace pe
{
	class PIXEL_ENGINE_API Texture : public sf::Texture, public Asset
	{
	public:
		inline Texture() {
			s_texture_count++;
			m_id = s_next_id++;
			m_name = std::string("tex_").append(std::to_string(m_id));
		}
		inline Texture(const std::string& name) : m_name(name) {
			s_texture_count++;
			m_id = s_next_id++;
		}

		inline ~Texture() { s_texture_count--; }

		inline bool loadFromFile(const std::string& path, const sf::IntRect& area = sf::IntRect()) {
			bool success = sf::Texture::loadFromFile(path, area);
			if (success) m_path = path;
			return success;
		}
		inline void setName(const std::string& name) { m_name = name; }

		inline const std::string& getName() const { return m_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Texture; }
		inline const std::string& getPath() const { return m_path; }

		inline static int getCount() { return s_texture_count; }

		//bool* _getSmoothPtr() {}

	private:
		friend class FileHandler;
		static int s_texture_count;
		static int s_next_id;
		std::string m_name;
		int m_id;
		std::string m_path;
	};
}