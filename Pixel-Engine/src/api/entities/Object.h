#pragma once
#include "..//core.h"

#include "Sprite.h"

namespace pe
{
	class PIXEL_ENGINE_API Object
	{
	public:
		~Object();
		inline glm::vec2 getPosition() { return m_position; }
		inline Sprite* getSprite() { return m_sprite; }

		void setPosition( glm::vec2 position );
		void setPosition( float x, float y );
		void setSprite( Sprite* sprite );
	private:
		Sprite* m_sprite;
		glm::vec2 m_position = glm::vec2(0,0);
	};
}