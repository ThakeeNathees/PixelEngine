#pragma once
#include "../core.h"

#include "pch.h"

namespace pe
{

	void drawVertexLine(sf::RenderTarget& render_target, sf::Vector2f point1, sf::Vector2f point2, sf::Color color = sf::Color::White) {
		sf::VertexArray line(sf::LinesStrip, 2);
		line[0].position = point1;
		line[0].color = color;
		line[1].position = point2;
		line[1].color = color;
		render_target.draw(line);
	}

	void drawVertexBox(sf::RenderTarget& rendet_target, sf::Vector2f point, sf::Vector2f size, sf::Color color = sf::Color::White) {
		drawVertexLine(rendet_target, sf::Vector2f(point.x, point.y), sf::Vector2f(point.x+size.x, point.y), color );
		drawVertexLine(rendet_target, sf::Vector2f(point.x+size.x, point.y), sf::Vector2f(point.x + size.x, point.y+size.y), color);
		drawVertexLine(rendet_target, sf::Vector2f(point.x + size.x, point.y+size.y), sf::Vector2f(point.x , point.y + size.y), color);
		drawVertexLine(rendet_target, sf::Vector2f(point.x , point.y + size.y), sf::Vector2f(point.x, point.y ), color);
	}

	/* draw line with thickness
		sf::RectangleShape r(sf::Vector2f(100,6));
		r.rotate(20); r.setFillColor(sf::Color::Blue);
		m_render_texture.draw(r);
	*/

}
