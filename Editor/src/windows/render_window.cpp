#include "pch.h"
#include "render_window.h"


sf::RenderTexture* RenderWindow::render_texture = new sf::RenderTexture();

void RenderWindow::renderRenderWindow()
{
	render_texture->create(100, 100);
	render_texture->clear({ 255,0,0,255 });
	ImGui::Begin("render window");
	ImGui::Image(*render_texture);
	ImGui::End();
}