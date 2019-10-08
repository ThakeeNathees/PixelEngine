#pragma once

#include "..//core.h"

#include "..//misc/Texture.h"
#include "Asset.h"

namespace pe {

	class PIXEL_ENGINE_API Sprite : public sf::Sprite, public Asset
	{
	public:
		inline Sprite() {
			s_sprite_count++;
			m_id = s_next_id++;
			m_name = std::string( "spr_").append(std::to_string(m_id));
		}
		inline Sprite(const std::string& name): m_name(name) {
			s_sprite_count++;
			m_id = s_next_id++;
		}
		inline ~Sprite() {
			s_sprite_count--;
		}
		Sprite(const Sprite& other) = delete;

		// setters
		inline void setName(const std::string& name) override { m_name = name; }
		void setTexture( Texture& texture, bool resetRect = false);
		void setFrames(int x, int y, int offset_x = 0, int offset_y = 0);
		void setFrames(const std::tuple<sf::Vector2i, sf::Vector2i>& frames);
		void setFrameIndex(int index);

		// getters
		inline const std::string& getName() const override { return m_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Sprite; }
		inline const std::tuple<sf::Vector2i, sf::Vector2i>& getFrames() const { return m_frames; }
		inline int getFrameCount() const { return std::get<0>(m_frames).x * std::get<0>(m_frames).y; }
		inline int getFrameIndex() const { return m_frame_index; }
		inline Texture& getTexture() const {
			if (m_texture == nullptr) throw std::exception("Error: in pe::Sprite::getTexture() const\n\ttexture was null");
			return *m_texture;
		}

		inline bool hasTexture() const { return m_texture != nullptr; }
		inline static int getCount() { return s_sprite_count; }

		

	private:
		friend class FileHandler;
		std::string m_name;
		static int s_sprite_count;
		static int s_next_id;
		int m_id;
		Texture* m_texture = nullptr;
		std::tuple<sf::Vector2i, sf::Vector2i> m_frames = std::make_tuple(sf::Vector2i(1, 1), sf::Vector2i(0, 0));
		int m_frame_index = 0;
	};

}

