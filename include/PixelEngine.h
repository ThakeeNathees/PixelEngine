#pragma once

#include "core/core.h"

/*
You can create yur custom entry point and main loop, if you want to use pixel engine's
entry point which have the crash handlers just implement the mainloop function
(symbol: int mainloop(int, char**)) as shown below, it'll link pixle engines main.
```
int mainloop(int argc, char** argv) {

	if (Engine::initialize() != 0) return 1;

	while (!glfwWindowShouldClose(Engine::get_window())) {
		glfwPollEvents();

		Engine::new_frame();
		//imgui_dockspace();
		//imgui_demo();
		Engine::clear();
		Engine::draw_frame();

		glfwSwapBuffers(Engine::get_window());
	}

	Engine::cleanup();
	return 0;
}
```
*/

