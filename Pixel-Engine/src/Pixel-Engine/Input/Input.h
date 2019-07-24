#pragma once

#include "..//Core.h"
#include "../Math/math.h"


namespace PE
{
	class PIXEL_ENGINE_API Input
	{
	public:
		enum Key{
			KEY_UNKNOWN = -1,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
			ESCAPE, Escape, LControl, LShift, LAlt, LSystem, RControl, RShift, RAlt, RSystem, Menu, LBracket,
			RBracket, Semicolon, Comma, Period, Quote, Slash, Backslash, Tilde, Equal, Hyphen, Space, Enter,
			Backspace, Tab, PageUp, PageDown, End, Home, Insert, Delete, Add, Subtract, Multiply, Divide,
			Left, Right, Up, Down,
			Numpad0, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8, Numpad9, F1, F2,
			F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		};
		enum Button {
			BUTTON_UNKNOWN =-1, MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE,
		};


		static bool isKeyPressed(Key key);
		static bool isButtonPressed( Button button );
		static vect2 getMousePosition(bool relative_to_window = true);					// defined in Window.cpp
		static void setMousePosition(vect2 position, bool relative_to_window = true);	// defined in Window.cpp


	};
}