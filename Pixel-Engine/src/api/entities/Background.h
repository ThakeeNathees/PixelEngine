#pragma once
#include "..//core.h"

namespace pe
{
	class PIXEL_ENGINE_API Background
	{
	public:
		Background();
		~Background();

		// setters
		void loadTexture(std::string path);
		inline void setVisible(bool visible) { m_visible = visible; }
		void setRepeatd(bool repeated);
		void setBgWindowSize(glm::ivec2 window_size);

		// getters
		inline bool getVisible() { return m_visible; }
		inline sf::Texture& getTexture() { return m_texture; }
		inline sf::Sprite& getBgSprite() { return m_background; }


	private:
		sf::Sprite m_background;
		sf::Texture m_texture;
		bool m_visible = false;
		bool m_is_repeated = false;
		glm::ivec2 m_window_size = glm::ivec2(-1, -1); // TODO: add horizoltal velocity

	};
}