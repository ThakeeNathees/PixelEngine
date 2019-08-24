#pragma once

#include "..//core.h"


namespace pe {

	class PIXEL_ENGINE_API Sprite : public sf::Sprite
	{
	public:
		Sprite();
		Sprite(const Sprite& other) = delete;
		bool loadTexture(const std::string& path, bool reset_rect = true);

		// setters
		void setFrames(int x, int y, int offset_x = 0, int offset_y = 0);
		void setFrameIndex(int index);

		// getters
		inline glm::ivec4 getFrames() const { return m_frames; }
		inline int getFrameCount() const { return m_frames.x * m_frames.y; }
		inline int getCurrentFrame() const { return m_frame_index; }
		inline int getId() const { return m_id; }
		

	private:
		static int s_sprite_count;
		int m_id;
		sf::Texture m_texture;
		glm::ivec4 m_frames = glm::ivec4(1, 1, 0, 0);
		int m_frame_index = 0;
	};

}

