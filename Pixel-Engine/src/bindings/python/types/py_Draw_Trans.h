#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "SFML/Graphics.hpp"

void register_draw_transform(py::module m)
{
	py::class_<sf::Drawable>(m, "Drawable");

	py::class_<sf::Transformable>(m, "Transformable")

		.def(py::init<>())
		.def("setPosition", (void (sf::Transformable::*)(float, float)) & sf::Transformable::setPosition)
		.def("setPosition", (void (sf::Transformable::*)(const sf::Vector2f&)) & sf::Transformable::setPosition)
		.def("setRotation", &sf::Transformable::setRotation)
		.def("setScale", (void (sf::Transformable::*)(float, float)) & sf::Transformable::setScale)
		.def("setScale", (void (sf::Transformable::*)(const sf::Vector2f&)) & sf::Transformable::setScale)
		.def("setOrigin", (void (sf::Transformable::*)(float, float)) & sf::Transformable::setOrigin)
		.def("setOrigin", (void (sf::Transformable::*)(const sf::Vector2f&)) & sf::Transformable::setOrigin)

		.def("getPosition", &sf::Transformable::getPosition)
		.def("getRotation", &sf::Transformable::getRotation)
		.def("getScale", &sf::Transformable::getScale)
		.def("getOrigin", &sf::Transformable::getOrigin)

		.def("move", (void (sf::Transformable::*)(float, float)) & sf::Transformable::move)
		.def("move", (void (sf::Transformable::*)(const sf::Vector2f&)) & sf::Transformable::move)
		.def("rotate", &sf::Transformable::rotate)
		.def("scale", (void (sf::Transformable::*)(float, float)) & sf::Transformable::scale)
		.def("scale", (void (sf::Transformable::*)(const sf::Vector2f&)) & sf::Transformable::scale)

		// TODO: getTransform, getinverseTransform
		;
}