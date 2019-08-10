#include "pch.h"
#include "render_window.h"


sf::RenderTexture* RenderWindow::render_texture = new sf::RenderTexture();

void RenderWindow::init() {
	render_texture->create(640, 480);
}

void RenderWindow::renderRenderWindow()
{
	render_texture->clear({ 50,50,50,255 });
	ImGui::Begin("render window");

	// size change callback
	static ImVec2 _size_old = ImGui::GetWindowSize();
	ImVec2 _size_new = ImGui::GetWindowSize();
	if ( ((_size_old.x != _size_new.x) || (_size_old.y != _size_new.y)) && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		unsigned int _w = ImGui::GetWindowSize().x - 15, _h = ImGui::GetWindowSize().y - 35;
		render_texture->create(_w, _h);
		_size_old = _size_new;
	}

	// draw / render things
	sf::Texture t;
	t.loadFromFile("res//logo.png");
	sf::Sprite s; s.setTexture(t);
	render_texture->draw(s);


	ImGui::Image(*render_texture);
	ImGui::End();
}