#pragma once
#include "..//core.h"

namespace pe
{
	class PIXEL_ENGINE_API Background : public sf::Drawable
	{
	public:
		Background();
		Background(const Background& other) = delete;
		~Background();

		// setters
		bool loadTexture(std::string path);
		inline void setVisible(bool visible) { m_visible = visible; }
		void setRepeatd(bool repeated);
		void setBgWindowSize(glm::ivec2 window_size);

		// getters
		inline bool getVisible() { return m_visible; }
		inline sf::Texture& getTexture() { return m_texture; }
		inline sf::Sprite& getBgSprite() { return m_background; }
		inline bool hasImage() const { return m_has_image; }



	private:
		friend class Application;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::Sprite m_background;
		sf::Texture m_texture;
		bool m_has_image = false; // set true when sprite initialized
		bool m_visible = true;
		bool m_is_repeated = false;
		glm::ivec2 m_window_size = glm::ivec2(-1, -1); // TODO: add horizoltal velocity
	};
}