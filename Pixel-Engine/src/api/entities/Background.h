#pragma once
#include "..//core.h"

#include "..//misc/Texture.h"
#include "Asset.h"

namespace pe
{
	class PIXEL_ENGINE_API Background : public sf::Drawable, public Asset
	{
	public:
		inline Background() {
			m_id = s_bg_count++;
			m_name = std::string( "background_").append(std::to_string(m_id));
		}
		inline Background(const std::string& name) : m_name(name) {
			m_id = s_bg_count++;
		}
		Background(const Background& other) = delete;
		inline ~Background(){}

		void move(glm::ivec2 vec);

		// setters
		inline void setName(const std::string& name) override { m_name = name; }
		inline void setVisible(bool visible) { m_visible = visible; }
		void setRepeatd(bool repeated);
		void setTextureRectSize(glm::ivec2 window_size, glm::ivec2 offset = glm::ivec2(0,0));
		void setTexture(pe::Texture* texture);

		// getters
		inline bool hasTexture() const {
			return m_texture != nullptr;
		}
		inline const std::string& getName() const override { return m_name; }
		inline bool getVisible() const { return m_visible; }
		inline bool getRepeat() const { return m_is_repeated; }
		inline Texture& getTexture() {
			assert(hasTexture() && "texture is nullptr");
			return *m_texture; 
		}
		inline sf::Sprite& getBgSprite() { return m_background; }
		inline const glm::ivec2& getTextureRectSize() const { return m_texture_rect_size; }
		inline const glm::ivec2& getTextureRectOffset() const { return { m_background.getTextureRect().left, m_background.getTextureRect().top }; }
		inline int getId() const { return m_id; }

	private:
		friend class AssetsReader;

		std::string m_name;
		static int s_bg_count;
		int m_id;
		friend class Application;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		Texture* m_texture = nullptr;
		sf::Sprite m_background;
		bool m_visible = true;
		bool m_is_repeated = false;
		glm::ivec2 m_texture_rect_size = glm::ivec2(-1, -1); // TODO: add horizoltal velocity
	};
}