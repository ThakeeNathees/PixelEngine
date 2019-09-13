#include "pch.h"
#include "entities.h"

#include <pybind11/stl.h>
#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/Application.h"

void register_animation(py::module& m)
{
	py::class_<pe::Track::Data>(m, "_TrackData")
		.def(py::init<>())
		.def(py::init<int>())
		.def(py::init<float>())
		.def(py::init<const sf::Vector2f&>())
		.def_readwrite("sprite_frame", &pe::Track::Data::sprite_frame)
		.def_readwrite("rotation", &pe::Track::Data::rotation)
		.def_readwrite("position", &pe::Track::Data::position)
		.def_readwrite("scale", &pe::Track::Data::scale)
		;
	py::class_<pe::Track::Key>(m, "_TrackKey")
		.def(py::init<>())
		.def(py::init<float, const pe::Track::Data&>())
		.def_readwrite("time", &pe::Track::Key::time)
		.def_readwrite("data", &pe::Track::Key::data)
		;

	py::class_<pe::Track>(m, "__Track")
		.def("addKey", [](pe::Track& self, const pe::Track::Key& key) { self.addKey(key); })
		.def("getData", [](pe::Track& self, float time) {self.getData(time); }, py::return_value_policy::reference)
		.def("getKeys", [](pe::Track& self) {return self.getKeys(); }, py::return_value_policy::reference)
		;

	py::class_<pe::SpriteFrameTrack, pe::Track>(m, "_SpriteFrameTrack").def(py::init<>());
	py::class_<pe::PositionTrack, pe::Track>(m, "_PositionTrack").def(py::init<>());
	py::class_<pe::RotationTrack, pe::Track>(m, "_RotationTrack").def(py::init<>());
	py::class_<pe::ScaleTrack, pe::Track>(m, "_ScaleTrack").def(py::init<>());

	////////////////////////////////////////////////////////////////////////////////////


	py::class_<pe::Animation, pe::Asset>(m, "Animation")
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("new", []() { return pe::Assets::newAsset<pe::Animation>(); }, py::return_value_policy::reference)
		.def_static("new", [](const std::string& name) { return pe::Assets::newAsset<pe::Animation>(name); }, py::return_value_policy::reference)
		.def("play", [](pe::Animation& self) {self.play(); })
		.def("reset", [](pe::Animation& self) {self.reset(); })
		.def("stop", [](pe::Animation& self) {self.stop(); })

		.def("setLoop", [](pe::Animation& self, bool loop) {self.setLoop(loop); })
		.def("setReverse", [](pe::Animation& self, bool reverse) {self.setReverse(reverse); })
		.def("setTimeLength", [](pe::Animation& self, float time_len) {self.setTimeLength(time_len); })

		.def("setSpriteFrameTrack", [](pe::Animation& self, pe::SpriteFrameTrack* sprite_frame_track) {self.setSpriteFrameTrack(sprite_frame_track); })
		.def("setPositionTrack", [](pe::Animation& self, pe::PositionTrack* pos_track) {self.setPositionTrack(pos_track); })
		.def("setRotationTrack", [](pe::Animation& self, pe::RotationTrack* rot_track) {self.setRotationTrack(rot_track); })
		.def("setScaleTrack", [](pe::Animation& self, pe::ScaleTrack* scale_track) {self.setScaleTrack(scale_track); })


		.def("isLoop", [](pe::Animation& self) {return self.isLoop(); })
		.def("isReverse", [](pe::Animation& self) {return self.isReverse(); })
		.def("getTimeLength", [](pe::Animation& self) {return self.getTimeLength(); })
		.def("getAnimEndSignal", [](pe::Animation& self) {return self.getAnimEndSignal(); }, py::return_value_policy::reference)
		.def("getBeginPosition", [](pe::Animation& self) {return self.getBeginPosition(); })
		.def("getBeginRotation", [](pe::Animation& self) {return self.getBeginRotation(); })
		.def("getBeginScale", [](pe::Animation& self) {return self.getBeginScale(); })

		.def("getSpriteFrameTrack", [](pe::Animation& self) {return self.getSpriteFrameTrack(); }, py::return_value_policy::reference)
		.def("getPositionTrack", [](pe::Animation& self) {return self.getPositionTrack(); }, py::return_value_policy::reference)
		.def("getRotationTrack", [](pe::Animation& self) {return self.getRotationTrack(); }, py::return_value_policy::reference)
		.def("getScaleTrack", [](pe::Animation& self) {return self.getScaleTrack(); }, py::return_value_policy::reference)

		.def("setObject", [](pe::Animation& self, pe::Object* obj) {self.setObject(obj); }, py::return_value_policy::reference)
		.def("getObject", [](pe::Animation& self) {return self.getObject(); }, py::return_value_policy::reference)
		;

}
