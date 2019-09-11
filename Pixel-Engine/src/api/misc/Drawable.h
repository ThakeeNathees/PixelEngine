#pragma once
#include "..//core.h"

namespace pe
{
	class PIXEL_ENGINE_API Drawable : public sf::Drawable
	{
	public:
		virtual int getZindex() const = 0;
		virtual void setZindex(int z_index) = 0;

		virtual void setVisible(bool visible) = 0;
		virtual bool isVisible() const = 0;
	};
}