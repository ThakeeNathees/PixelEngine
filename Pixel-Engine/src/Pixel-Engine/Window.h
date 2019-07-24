#pragma once

#include "Core.h"
#include "Math/math.h"
#include "Input/Event.h"


namespace PE {
	class Application;
	class Input;
}


namespace PE
{
	class PIXEL_ENGINE_API Window
	{
	public:
		struct Prop
		{
			std::string title;
			vect2 size;
			vect2 position;
		};
		virtual void Init() = 0;
		
		// getters
		virtual vect2 getSize() const = 0;
		virtual vect2 getPosition() const = 0;
		virtual std::string getTitle() const = 0;
		virtual bool isOpen() const = 0;

		// setters
		virtual void setPosition(const vect2& pos) = 0;

	protected:
		Prop m_prop;
		static bool s_is_window_created;

	private:
		friend Application;
		static std::shared_ptr<Window> create(const Window::Prop& prop = { "Pixel-Engine", vect2(640, 480), vect2(-1,-1) });
	};
}