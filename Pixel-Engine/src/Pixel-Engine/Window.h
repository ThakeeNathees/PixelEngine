#pragma once
#include "Core.h"
#include "Math/math.h"

namespace PE
{
	class Window
	{
	public:
		Window();
		virtual ~Window() = 0;

		struct Prop
		{
			std::string title;
			vect2 size;
			vect2 position;
		};

		inline void Init(const Window::Prop& prop = { "Pixel-Engine", vect2(640, 480), vect2(200,200) })
		{
			m_prop = prop;
		}

		virtual vect2 getSize() = 0;
		virtual vect2 getPosition() = 0;
		virtual std::string getTitle() = 0;

	private:
		Prop m_prop;


	};
}