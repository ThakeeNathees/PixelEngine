#include "pch.h"
#include "render_window.h"

//TEST : remove
pe::Sprite* RenderWindow::test_sprite;

sf::RenderTexture* RenderWindow::s_render_texture = new sf::RenderTexture();
glm::vec2 RenderWindow::s_mouse_pos = glm::vec2(0,0);

void RenderWindow::init() {
	s_render_texture->create(640, 480);
}

void RenderWindow::listenEvent(sf::Event& event) {
	
}

void RenderWindow::renderRenderWindow()
{
	s_render_texture->clear({ 80,80,80,255 }); // MAGIC NUMBER
	ImGui::Begin("render window");

	// size change callback
	static ImVec2 _size_old = ImGui::GetWindowSize();
	ImVec2 _size_new = ImGui::GetWindowSize();
	if ( ((_size_old.x != _size_new.x) || (_size_old.y != _size_new.y)) && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		unsigned int _w = ImGui::GetWindowSize().x - 15, _h = ImGui::GetWindowSize().y - 35;
		s_render_texture->create(_w, _h);
		_size_old = _size_new;
	}
	s_mouse_pos.x = ImGui::GetMousePos().x - ImGui::GetWindowPos().x;
	s_mouse_pos.y = ImGui::GetMousePos().y - ImGui::GetWindowPos().y;

	// draw / render things
	s_render_texture->draw(*test_sprite);


	ImGui::Image(*s_render_texture);
	ImGui::End();
}