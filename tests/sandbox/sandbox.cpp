#include "PixelEngine.h"
using namespace pe;

int mainloop(int argc, char** argv) {

	if (Glfw_ImGui::initialize() != 0) return 1;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(Glfw_ImGui::get_window())) {
		glfwPollEvents();

		Glfw_ImGui::new_frame();
		//imgui_dockspace();
		ImGui::ShowDemoWindow();
		//imgui_demo();
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		Glfw_ImGui::draw_frame();


		// opengl rendering

		glfwSwapBuffers(Glfw_ImGui::get_window());
	}

	Glfw_ImGui::cleanup();
	return 0;
}