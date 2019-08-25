#pragma once
#include "..//core.h"

namespace pe
{
	class PIXEL_ENGINE_API Background : public sf::Drawable
	{
	public:
		inline Background() {
			m_id = s_bg_count++;
			m_name = std::string( "background_", m_id );
		}
		inline Background(const std::string& name) : m_name(name) {
			m_id = s_bg_count++;
		}
		Background(const Background& other) = delete;
		inline ~Background(){}

		// setters
		inline void setName(const std::string& name) { m_name = name; }
		bool loadTexture(std::string path);
		inline void setVisible(bool visible) { m_visible = visible; }
		void setRepeatd(bool repeated);
		void setBgWindowSize(glm::ivec2 window_size);

		// getters
		inline const std::string& getName() const { return m_name; }
		inline bool getVisible() { return m_visible; }
		inline sf::Texture& getTexture() { return m_texture; }
		inline sf::Sprite& getBgSprite() { return m_background; }
		inline bool hasImage() const { return m_has_image; }



	private:
		std::string m_name;
		static int s_bg_count;
		int m_id;
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