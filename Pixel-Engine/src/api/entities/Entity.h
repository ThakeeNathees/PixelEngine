#pragma once
#include "..//core.h"


#include "pch.h"


namespace pe
{
	class PIXEL_ENGINE_API Entity
	{
	public:
		virtual std::vector<sf::Drawable*> getDrawables() = 0;
		virtual glm::vec4 getSelectableArea() = 0; // for editor to draw a rectangle and draw
	};
}