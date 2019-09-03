#pragma once
#include "..//core.h"
#include "..//misc/Texture.h"

namespace pe
{
	class PIXEL_ENGINE_API Background : public sf::Sprite, public Asset
	{
	public:
		inline Background() {
			s_bg_count++;
			m_id = s_next_id++;
			m_name = std::string( "bg_").append(std::to_string(m_id));
		}
		inline Background(const std::string& name) : m_name(name) {
			s_bg_count++;
			m_id = s_next_id++;
		}
		Background(const Background& other) = delete;
		inline ~Background(){
			s_bg_count--;
		}

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
		void setTexture(pe::Texture& texture);
		inline void setMoveSpeed(int x, int y) { setMoveSpeed({x,y}); }
		inline void setMoveSpeed(glm::ivec2 speed) { m_move_speed = speed; }

		// getters
		inline const std::string& getName() const override { return m_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Background; }


		inline bool isVisible() const { return m_visible; }
		inline bool isRepeat() const { return m_texture->isRepeated(); }
		inline bool isSmooth() const { return m_texture->isSmooth(); }
		inline Texture& getTexture() { assert(m_texture); return *m_texture; }
		inline const glm::ivec2& getMoveSpeed() const { return m_move_speed; }

		inline bool hasTexture() const { return m_texture != nullptr; }


	private:
		friend class AssetsReader;
		friend class Application; // call move
		friend class Scene;
		void setTextureRectSize(glm::ivec2 window_size, glm::ivec2 offset = glm::ivec2(0,0));
		void move(double dt);

		std::string m_name;
		static int s_bg_count;
		static int s_next_id;
		int m_id;
		friend class Application;
		Texture* m_texture = nullptr;
		bool m_visible = true;
		glm::ivec2 m_move_speed = glm::ivec2(0,0);
	};
}