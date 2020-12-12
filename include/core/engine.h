#pragma once

#include "core/internal.h"
#include "gl_loader.h"

namespace pe {

class Engine {
public:

	// TODO: window title and dimension hardcoded.
	static int initialize();
	static void cleanup();

	static bool poll_event(/*Event& event*/);
	static void new_frame();
	static void draw_frame();
	static void swap_buffer();
	static void clear();

	// TODO: create wrappers
#if defined(GL_LOADER_SDL)
	static SDL_Window* get_window();
private:
	static SDL_Window* window;
	static SDL_GLContext gl_context;
#elif defined(GL_LOADER_GLFW)
	static GLFWwindow* get_window();
private:
	static GLFWwindow* window;
#endif
};

}