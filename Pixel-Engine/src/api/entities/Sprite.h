#pragma once

#include "..//core.h"


namespace pe {

	class Sprite : public sf::Sprite
	{
	public:
		bool loadTexture(const char* path);
		//void setTexture(const sf::Texture& texture); in sfml

		// setters
		void setFrames(glm::vec2 frame);
		void setFrameIndex(int index);

		// getters
		glm::vec2 getFrames() const { return m_frames; }

	private:
		sf::Texture m_texture;
		bool visible = true;
		glm::vec2 m_frames;
		int m_frame_index;
	};

}

