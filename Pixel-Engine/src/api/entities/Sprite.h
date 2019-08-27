#pragma once

#include "..//core.h"

#include "..//misc/Texture.h"
#include "Asset.h"

namespace pe {

	class PIXEL_ENGINE_API Sprite : public sf::Sprite, public Asset
	{
	public:
		inline Sprite() {
			m_id = s_sprite_count++;
			m_name = std::string( "Sprite_").append(std::to_string(m_id));
		}
		inline Sprite(const std::string& name): m_name(name) {
			m_id = s_sprite_count++;
		}

		Sprite(const Sprite& other) = delete;

		// setters
		void setTexture( Texture* texture, bool resetRect = false);
		inline void setName(const std::string& name) override { m_name = name; }
		void setFrames(int x, int y, int offset_x = 0, int offset_y = 0);
		void setFrames(const glm::ivec4& frames);
		void setFrameIndex(int index);

		// getters
		inline const std::string& getName() const override { return m_name; }
		inline glm::ivec4 getFrames() const { return m_frames; }
		inline int getFrameCount() const { return m_frames.x * m_frames.y; }
		inline int getCurrentFrame() const { return m_frame_index; }
		inline int getId() const override { return m_id; }
		inline Texture& getTexture() const { 
			assert( hasTexture() && "texture is nullptr" );
			return *m_texture;
		}

		inline bool hasTexture() const { return m_texture != nullptr; }
		

	private:
		friend class AssetsReader;
		std::string m_name;
		static int s_sprite_count;
		int m_id;
		Texture* m_texture = nullptr;
		glm::ivec4 m_frames = glm::ivec4(1, 1, 0, 0);
		int m_frame_index = 0;
	};

}

