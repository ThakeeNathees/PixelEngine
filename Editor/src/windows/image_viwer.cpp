#include "pch.h"
#include "image_viwer.h"

bool ImageViwer::s_p_open = false;
sf::Texture ImageViwer::s_texture;


void ImageViwer::setImage(const char* path)
{
	s_texture.loadFromFile(path);
	s_p_open = true;
}


void ImageViwer::renderImageViwer()
{
	if (s_p_open) {

		ImGui::Begin("Image-Viwer", &s_p_open);
		ImGui::Image(s_texture);
		ImGui::End();

	}
}