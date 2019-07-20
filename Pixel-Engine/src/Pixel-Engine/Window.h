#pragma once

#include "Pixel-Engine/Core.h"

namespace PE
{
	struct WindowProps
	{
		//std::string title;
		unsigned int width, height;

	};

	class PIXEL_ENGINE_API Window
	{
	public:
		//using EventCallbackFunc = std::function<void(Event&)>;
		
		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth()  const = 0;
		virtual unsigned int getHeight() const = 0;

		// window attributes
		//virtual void setEventCallback( const EventCallbackFunc& callback ) = 0;
		virtual void setVSync(bool enable) = 0;
		virtual bool isVSync() const = 0;

		//static Window* create(const WindowProps& window_props = WindowProps()); // implement in a platform specific file
	};



}