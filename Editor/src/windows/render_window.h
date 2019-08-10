#pragma once


class RenderWindow
{
public:
	static void init();
	static void renderRenderWindow();

private:
	static sf::RenderTexture* render_texture;
};