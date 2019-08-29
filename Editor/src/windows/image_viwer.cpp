#include "pch.h"
#include "image_viwer.h"

bool ImageViwer::s_p_open = false;
bool ImageViwer::s_texture_smooth = false;
pe::Texture ImageViwer::s_texture;
pe::Sprite ImageViwer::s_sprite;
sf::RenderTexture ImageViwer::s_render_texture;
sf::Vector2f ImageViwer::s_mouse_middle_pos;
sf::Vector2f ImageViwer::s_sprite_init_pos;

void ImageViwer::init()
{
	s_texture.setSmooth(false); // TODO: add buttons
}


void ImageViwer::setImage(const char* path)
{
	s_texture.loadFromFile(path);
	s_sprite.setTexture(s_texture, true);
	s_sprite.setScale(1,1);
	s_sprite.setPosition(0,0);
	s_render_texture.draw(s_sprite);
	s_p_open = true;
}

void ImageViwer::listenEvent(sf::Event& event) {
	if ( s_p_open ){
		if (event.type == sf::Event::MouseWheelMoved) {
			int delta = event.mouseWheel.delta;
			s_sprite.scale(1 + delta / 20.f, 1 + delta / 20.f);
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Middle){
			s_mouse_middle_pos.x = event.mouseButton.x;
			s_mouse_middle_pos.y = event.mouseButton.y;
			s_sprite_init_pos = s_sprite.getPosition();
		}
		if ( sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
			if (event.type == sf::Event::MouseMoved) {
				s_sprite.setPosition(
					sf::Vector2f(event.mouseMove.x, event.mouseMove.y) - s_mouse_middle_pos + s_sprite_init_pos
				);

			}
		}
	}
}

void ImageViwer::renderImageViwer()
{
	if (s_p_open) {
		ImGui::Begin("Image-Viwer", &s_p_open); 
		if (ImGui::Button("smooth")) { // TODO: move this as a menu bar
			s_texture.setSmooth( ! s_texture.isSmooth() );
		}
		s_render_texture.create(ImGui::GetWindowSize().x-10, ImGui::GetWindowSize().y-80);
		s_render_texture.clear(sf::Color(255,255,255,255)); // TODO : color and other magic numbers
		s_render_texture.draw(s_sprite);
		ImGui::Image(s_render_texture);
		ImGui::End();

	}
}