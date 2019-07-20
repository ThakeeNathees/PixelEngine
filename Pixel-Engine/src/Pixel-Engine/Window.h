#pragma once

#include "Pixel-Engine/Core.h"
#include "Pixel-Engine/Events/Event.h"



namespace PE
{
	class PIXEL_ENGINE_API Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;
		
		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth()  const = 0;
		virtual unsigned int getHeight() const = 0;

		// window attributes
		virtual void setEventCallback( const EventCallbackFunc& callback ) = 0;
		virtual void setVSync(bool enable) = 0;
		virtual bool isVSync() const = 0;

		static Window* create(const WindowProps& window_props = WindowProps());
	};


	struct WindowProps
	{
		std::string title;
		unsigned int width, height;

		WindowProps( const std::string& title = "Pixel-Engine", unsigned int width=640, unsigned int hieght=480 )
			:title(title), width(width), height(height)
		{}
	};

}