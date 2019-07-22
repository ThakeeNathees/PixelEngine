#pragma once
#include "Core.h"

#include "Math/math.h"

namespace PE
{
	class Window
	{
	public:
		
		struct Prop
		{
			std::string title;
			vect2 size;
			vect2 position;
		};
		static std::shared_ptr<Window> create(const Window::Prop& prop = { "Pixel-Engine", vect2(640, 480), vect2(-1,-1) });
		virtual void Init() = 0;
		
		// getters
		virtual vect2 getSize() const = 0;
		virtual vect2 getPosition() const = 0;
		virtual std::string getTitle() const = 0;
		virtual bool isOpen() const = 0;

	protected:
		Prop m_prop;
	};
}