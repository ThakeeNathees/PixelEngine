#include <stdio.h>

#include "pe_im.h"

int main(int, char**) {

	GLFWwindow* window = peglfw__init(1280, 720, "Dear ImGui GLFW+OpenGL3 example");
	peimgui__init(window);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		peimgui__new_frame();
		/*****************************/
		peimgui__dockspace();
		peimgui__demo();

		/*****************************/
		peimgui__render(window);
		glfwSwapBuffers(window);
	}

	peimgui__cleanup();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;

}