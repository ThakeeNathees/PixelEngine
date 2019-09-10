#pragma once

#include <pybind11/stl.h>
#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/entities/Animation.h"

#include <SFML/Window.hpp>
void register_animation(py::module& m)
{
	py::class_<pe::Track::Data>(m, "TrackData")
		.def(py::init<>())
		.def(py::init<int>())
		.def(py::init<float>())
		.def(py::init<const sf::Vector2f&>())
		.def_readwrite("sprite_frame", &pe::Track::Data::sprite_frame)
		.def_readwrite("rotation", &pe::Track::Data::rotation)
		.def_readwrite("position", &pe::Track::Data::position)
		.def_readwrite("scale", &pe::Track::Data::scale)
		;
	py::class_<pe::Track::Key>(m, "TrackKey")
		.def(py::init<>())
		.def(py::init<float, const pe::Track::Data&>())
		.def_readwrite("time", &pe::Track::Key::time)
		.def_readwrite("data", &pe::Track::Key::data)
		;

	py::class_<pe::Track>(m, "_Track")
		.def("addKey", &pe::Track::addKey)
		.def("getData", &pe::Track::getData)
		.def("getKeys", &pe::Track::getKeys)
		;
	
	py::class_<pe::SpriteFrameTrack, pe::Track>(m, "SpriteFrameTrack").def(py::init<>());
	py::class_<pe::PositionTrack, pe::Track>(m, "PositionTrack").def(py::init<>());
	py::class_<pe::RotationTrack, pe::Track>(m, "RotationTrack").def(py::init<>());
	py::class_<pe::ScaleTrack, pe::Track>(m, "ScaleTrack").def(py::init<>());

	////////////////////////////////////////////////////////////////////////////////////


	py::class_<pe::Animation, pe::Asset>(m, "Animation")
		.def(py::init<>())
		.def(py::init<py::str>())
		.def("play", &pe::Animation::play)
		.def("reset", &pe::Animation::reset)
		.def("stop", &pe::Animation::stop)

		.def("setLoop", &pe::Animation::setLoop)
		.def("setReverse", &pe::Animation::setReverse)
		.def("setTimeLength", &pe::Animation::setTimeLength)

		.def("setSpriteFrameTrack", &pe::Animation::setSpriteFrameTrack)
		.def("setPositionTrack", &pe::Animation::setPositionTrack)
		.def("setRotationTrack", &pe::Animation::setRotationTrack)
		.def("setScaleTrack", &pe::Animation::setScaleTrack)


		.def("isLoop", &pe::Animation::isLoop)
		.def("isReverse", &pe::Animation::isReverse)
		.def("getTimeLength", &pe::Animation::getTimeLength)
		.def("getAnimEndSignal", &pe::Animation::getAnimEndSignal)
		.def("getBeginPosition", &pe::Animation::getBeginPosition)
		.def("getBeginRotation", &pe::Animation::getBeginRotation)
		.def("getBeginScale", &pe::Animation::getBeginScale)

		.def("getSpriteFrameTrack", &pe::Animation::getSpriteFrameTrack)
		.def("getPositionTrack", &pe::Animation::getPositionTrack)
		.def("getRotationTrack", &pe::Animation::getRotationTrack)
		.def("getScaleTrack", &pe::Animation::getScaleTrack)

		.def("setObject", &pe::Animation::setObject)
		.def("getObject", &pe::Animation::getObject)
		;

}
