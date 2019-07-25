#pragma once

#include "..//Core.h"



namespace pe
{
	class PIXEL_ENGINE_API Input
	{
	public:
		enum Key{
			KEY_UNKNOWN = -1,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
			ESCAPE, LCONTROL, LSHIFT, LALT, LSYSTEM, RCONTROL, RSHIFT, RALT, RSYSTEM, MENU, LBRACKET,
			RBRACKET, SEMICOLON, COMMA, PERIOD, QUOTE, SLASH, BACKSLASH, TILDE, EQUAL, HYPHEN, SPACE, ENTER,
			BACKSPACE, TAB, PAGEUP, PAGEDOWN, END, HOME, INSERT, _DELETE, ADD, SUBTRACT, MULTIPLY, DIVIDE,
			LEFT, RIGHT, UP, DOWN,
			NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9, F1, F2,
			F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		};
		enum Button {
			BUTTON_UNKNOWN =-1, MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE,
		};


		static bool isKeyPressed(Key key);
		static bool isButtonPressed( Button button );
		static vec2 getMousePosition(bool relative_to_window = true);					// defined in Window.cpp
		static void setMousePosition(vec2 position, bool relative_to_window = true);	// defined in Window.cpp


	};
}