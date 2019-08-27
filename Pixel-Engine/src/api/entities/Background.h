#pragma once
#include "..//core.h"

#include "..//misc/Texture.h"
#include "Asset.h"

namespace pe
{
	class PIXEL_ENGINE_API Background : public sf::Sprite, public Asset
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

		// deleted functions bg only have scale
		void setPosition() = delete;
		void setRotation() = delete;
		void setOrigin() = delete;
		void getPosition() = delete;
		void retRotation() = delete;
		void getOrigin() = delete;

		// setters
		inline void setName(const std::string& name) override { m_name = name; }
		inline void setVisible(bool visible) { m_visible = visible; }
		void setRepeatd(bool repeated);
		void setSmooth(bool smooth);
		void setTexture(pe::Texture* texture);
		inline void setMoveSpeed(int x, int y) { setMoveSpeed({x,y}); }
		inline void setMoveSpeed(glm::ivec2 speed) { m_move_speed = speed; }

		// getters
		inline const std::string& getName() const override { return m_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Backtround; }

		inline bool hasTexture() const { return m_texture != nullptr; }
		inline bool getVisible() const { return m_visible; }
		inline bool getRepeat() const { return m_repeated; }
		inline bool getSmooth() const { return m_smooth; }
		inline Texture& getTexture() { assert(hasTexture() && "texture is nullptr"); return *m_texture; }
		//inline const glm::ivec2& getTextureRectSize() const { return m_texture_rect_size; }
		//inline const glm::ivec2& getTextureRectOffset() const { return { getTextureRect().left, getTextureRect().top }; }
		inline const glm::ivec2& getMoveSpeed() const { return m_move_speed; }


	private:
		friend class AssetsReader;
		friend class Application; // call move
		friend class Scene;
		void setTextureRectSize(glm::ivec2 window_size, glm::ivec2 offset = glm::ivec2(0,0));
		void move(double dt);

		std::string m_name;
		static int s_bg_count;
		int m_id;
		friend class Application;
		Texture* m_texture = nullptr;
		bool m_visible = true;
		bool m_repeated = false;
		bool m_smooth = false;
		glm::ivec2 m_move_speed = glm::ivec2(0,0);
		//glm::ivec2 m_texture_rect_size = glm::ivec2(-1, -1);
	};
}