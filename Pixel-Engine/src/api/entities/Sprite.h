#pragma once

#include "..//core.h"


namespace pe {

	class Sprite : public sf::Sprite
	{
	public:
		Sprite();
		bool loadTexture(const char* path);
		//void setTexture(const sf::Texture& texture); in sfml

		// setters
		inline void setFrames(int x, int y, int offset_x = 0, int offset_y = 0) {
			m_frames.x = x; m_frames.y = y; m_frames.z = offset_x; m_frames.w = offset_y;
		}
		void setFrameIndex(int index);

		// getters
		inline glm::ivec4 getFrames() const { return m_frames; }

	private:
		static int s_id;
		sf::Texture m_texture;
		bool visible = true;
		glm::ivec4 m_frames = glm::ivec4(1, 1, 0, 0);
		int m_frame_index;
	};

}

