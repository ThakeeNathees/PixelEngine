#include "PixelEngine.h"
using namespace pe;

int mainloop(int argc, char** argv) {

	if (Engine::initialize() != 0) return 1;

	while (!glfwWindowShouldClose(Engine::get_window())) {
		glfwPollEvents();

		Engine::new_frame();
		//imgui_dockspace();
		//imgui_demo();
		Engine::draw_frame();

		// opengl rendering

		glfwSwapBuffers(Engine::get_window());
	}

	Engine::cleanup();
	return 0;
}