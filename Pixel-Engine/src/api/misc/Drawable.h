#pragma once
#include "..//core.h"

namespace pe
{
	class PIXEL_ENGINE_API Drawable : public sf::Drawable
	{
	public:
		virtual int getZIndex() const = 0;
		virtual void setZIndex(int z_index) = 0;

		virtual void setVisible(bool visible) = 0;
		virtual bool getVisible() const = 0;
	};
}