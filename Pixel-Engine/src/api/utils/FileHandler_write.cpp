#include "pch.h"
#include "FileHandler.h"

#include "tinyxml2.h"
#include "bindings/python/PythonObject.h"

namespace pe
{
	FileHandler::FileHandler()
	{
		m_doc = new tinyxml2::XMLDocument();
	}

	int FileHandler::writeProject(const struct _peproj& proj, const char* path) {
		m_doc->Clear();

		auto root = m_doc->NewElement("Project");
		root->SetAttribute("title", proj.title.c_str());
		m_doc->InsertFirstChild(root);

		auto size_tag = m_doc->NewElement("window_size");
		root->InsertEndChild(size_tag);
		size_tag->SetAttribute("x", proj.window_size.x);
		size_tag->SetAttribute("y", proj.window_size.y);

		auto pref_tag = m_doc->NewElement("pref");
		root->InsertEndChild(pref_tag);
		pref_tag->SetAttribute("frame_rate", proj.frame_rate);
		pref_tag->SetAttribute("begin_scene_id", proj.begin_scene_id);
		pref_tag->SetAttribute("debug_mode", proj.is_debug_mode);
		pref_tag->SetAttribute("no_console", proj.no_console_window);

		int id = proj.logo_texture_id;
		if (id >= 0) {
			auto window_icon_tag = m_doc->NewElement("logo_texture");
			root->InsertEndChild(window_icon_tag);
			window_icon_tag->SetAttribute("id", proj.logo_texture_id);
		}

		auto bg_color = m_doc->NewElement("bg_color");
		root->InsertEndChild(bg_color);
		bg_color->SetAttribute("r", proj.default_bg_color.r);
		bg_color->SetAttribute("g", proj.default_bg_color.g);
		bg_color->SetAttribute("b", proj.default_bg_color.b);
		bg_color->SetAttribute("a", proj.default_bg_color.a);

		auto assets_tag = m_doc->NewElement("assets");
		root->InsertEndChild(assets_tag);
		assets_tag->SetText(proj.assets_path.c_str());

		auto objects_tag = m_doc->NewElement("objects");
		root->InsertEndChild(objects_tag);
		for (auto path : proj.objects_path) {
			auto path_tag = m_doc->NewElement("path");
			objects_tag->InsertEndChild(path_tag);
			path_tag->SetText(path.c_str());
		}

		auto scenes_tag = m_doc->NewElement("scenes");
		root->InsertEndChild(scenes_tag);
		for (auto path : proj.scene_paths) {
			auto path_tag = m_doc->NewElement("path");
			scenes_tag->InsertEndChild(path_tag);
			path_tag->SetText(path.c_str());
		}
		auto str_path = std::string(path);
		if (str_path[str_path.length() - 1] != '/' || str_path[str_path.length() - 1] != '\\')
			str_path.append("/");
		return m_doc->SaveFile(str_path.append(proj.title).append(".test.peproj.xml").c_str());

	} // peproj

	int FileHandler::writeObject(Object* obj, const char* path) {
		m_doc->Clear();
		auto obj_tag = m_doc->NewElement("object");
		m_doc->InsertFirstChild(obj_tag);

		/*
		switch (obj->getOjbectType()) {
		case Object::ObjectType::CPP_OBJECT:
			obj_tag->SetAttribute("type", "CPP_OBJECT");
			break;
		case Object::ObjectType::PYTHON_OBJECT:
			obj_tag->SetAttribute("type", "PYTHON_OBJECT");
			break;
		}
		obj_tag->SetAttribute("class_name", obj->getClassName().c_str());
		*/
		obj_tag->SetAttribute("name", obj->getName().c_str());
		obj_tag->SetAttribute("id", obj->getId());

		auto class_tag = m_doc->NewElement("class");
		obj_tag->InsertEndChild(class_tag);
		class_tag->SetAttribute("name", obj->m_class_name.c_str());
		switch (obj->getOjbectType()) {
		case Object::ObjectType::CPP_OBJECT:
			class_tag->SetAttribute("type", "CPP_OBJECT");
			break;
		case Object::ObjectType::PYTHON_OBJECT:
			class_tag->SetAttribute("type", "PYTHON_OBJECT");
			break;
		}
		class_tag->SetText(obj->m_class_path.c_str());

		auto prop = m_doc->NewElement("properties");
		obj_tag->InsertEndChild(prop);
		prop->SetAttribute("z_index", obj->getZindex());
		prop->SetAttribute("visible", obj->isVisible());
		prop->SetAttribute("persistence", obj->isPersistence());

		auto transform_tag = m_doc->NewElement("transform");
		obj_tag->InsertEndChild(transform_tag);

		auto pos_tag = m_doc->NewElement("position");
		transform_tag->InsertEndChild(pos_tag);
		pos_tag->SetAttribute("x", obj->getPosition().x);
		pos_tag->SetAttribute("y", obj->getPosition().y);
		auto rot_tag = m_doc->NewElement("rotation");
		transform_tag->InsertEndChild(rot_tag);
		rot_tag->SetAttribute("angle", obj->getRotation());
		auto scale_tag = m_doc->NewElement("scale");
		transform_tag->InsertEndChild(scale_tag);
		scale_tag->SetAttribute("x", obj->getScale().x);
		scale_tag->SetAttribute("y", obj->getScale().y);
		auto origin_tag = m_doc->NewElement("origin");
		transform_tag->InsertEndChild(origin_tag);
		origin_tag->SetAttribute("x", obj->getOrigin().x);
		origin_tag->SetAttribute("y", obj->getOrigin().y);

		if (obj->hasSprite()) {
			setSprite(obj_tag, obj->getSprite());
		}
		if (obj->hasArea()) {
			setArea(obj_tag, obj->getArea());
		}

		auto anims_tag = m_doc->NewElement("animations");
		obj_tag->InsertEndChild(anims_tag);
		for (auto anim : obj->getAnimations()) {
			addAnimation(anims_tag, anim.second);
		}
		auto str_path = std::string(path);
		if (str_path[str_path.length() - 1] != '/' || str_path[str_path.length() - 1] != '\\')
			str_path.append("/");
		return m_doc->SaveFile( str_path.append(std::to_string(obj->getId())).append(".obj.xml").c_str()  );

	} // write object

	int FileHandler::writeScene(Scene* scene, const char* path) {
		m_doc->Clear();
		auto scn_tag = m_doc->NewElement("scene");
		m_doc->InsertEndChild(scn_tag);
		scn_tag->SetAttribute("name", scene->getName().c_str());
		scn_tag->SetAttribute("id", scene->getId());

		if (auto bg = scene->getBackground()) {
			auto bg_tag = m_doc->NewElement("background");
			scn_tag->InsertEndChild(bg_tag);
			bg_tag->SetAttribute("name", bg->getName().c_str());
			bg_tag->SetAttribute("id", bg->getId());

			auto prop = m_doc->NewElement("properties");
			bg_tag->InsertEndChild(prop);
			prop->SetAttribute("visible", bg->isVisible());

			auto speed_tag = m_doc->NewElement("move_speed");
			bg_tag->InsertEndChild(speed_tag);
			speed_tag->SetAttribute("x", bg->getMoveSpeed().x);
			speed_tag->SetAttribute("y", bg->getMoveSpeed().y);

			auto scale_tag = m_doc->NewElement("scale");
			bg_tag->InsertEndChild(scale_tag);
			scale_tag->SetAttribute("x", bg->getScale().x);
			scale_tag->SetAttribute("y", bg->getScale().y);

			if (bg->hasTexture()) {
				auto texture_tag = m_doc->NewElement("texture");
				bg_tag->InsertEndChild(texture_tag);
				texture_tag->SetAttribute("id", bg->getTexture().getId());
			}
		}

		auto objs_tag = m_doc->NewElement("objects");
		scn_tag->InsertEndChild(objs_tag);
		for (Object* obj : scene->m_objects) {
			auto obj_tag = m_doc->NewElement("object");
			objs_tag->InsertEndChild(obj_tag);
			obj_tag->SetAttribute("id", obj->getId());
		}

		auto str_path = std::string(path);
		if (str_path[str_path.length() - 1] != '/' || str_path[str_path.length() - 1] != '\\')
			str_path.append("/");
		return m_doc->SaveFile(str_path.append(std::to_string(scene->getId())).append(".scn.xml").c_str());
	}

	//////////////////////////////////////////////////////////////////

	void FileHandler::setSprite(tinyxml2::XMLElement* obj_tag, Sprite& sprite) {

		auto sprite_tag = m_doc->NewElement("sprite");
		obj_tag->InsertEndChild(sprite_tag);
		sprite_tag->SetAttribute("name", sprite.getName().c_str());
		sprite_tag->SetAttribute("id", sprite.getId());


		if (sprite.hasTexture()) {
			auto texture_tag = m_doc->NewElement("texture");
			sprite_tag->InsertEndChild(texture_tag);
			texture_tag->SetAttribute("id", sprite.getTexture().getId());

			auto texture_rect_tag = m_doc->NewElement("texture_rect");
			sprite_tag->InsertEndChild(texture_rect_tag);
			texture_rect_tag->SetAttribute("left", sprite.getTextureRect().left);
			texture_rect_tag->SetAttribute("top", sprite.getTextureRect().top);
			texture_rect_tag->SetAttribute("width", sprite.getTextureRect().width);
			texture_rect_tag->SetAttribute("height", sprite.getTextureRect().height);

			auto frames_tag = m_doc->NewElement("frames");
			sprite_tag->InsertEndChild(frames_tag);
			frames_tag->SetAttribute("x", std::get<0>(sprite.getFrames()).x);
			frames_tag->SetAttribute("y", std::get<0>(sprite.getFrames()).y);
			frames_tag->SetAttribute("offset_x", std::get<1>(sprite.getFrames()).x);
			frames_tag->SetAttribute("offset_y", std::get<1>(sprite.getFrames()).y);
			frames_tag->SetAttribute("index", sprite.getFrameIndex());
		}
	}

	void FileHandler::setArea(tinyxml2::XMLElement* obj_tag, Area& area) {
		auto area_tag = m_doc->NewElement("area");
		obj_tag->InsertEndChild(area_tag);
		area_tag->SetAttribute("name", area.getName().c_str());
		area_tag->SetAttribute("id", area.getId());

		if (area.hasShape()) {
			auto shape_tag = m_doc->NewElement("shape");
			area_tag->InsertEndChild(shape_tag);
			shape_tag->SetAttribute("point_count", (int)area.getShape().getPointCount());
			for (int i = 0; i < area.getShape().getPointCount(); i++) {
				auto point_tag = m_doc->NewElement("point");
				shape_tag->InsertEndChild(point_tag);
				point_tag->SetAttribute("index", i);
				point_tag->SetAttribute("x", area.getShape().getPoint(i).x);
				point_tag->SetAttribute("y", area.getShape().getPoint(i).y);
			}
		}
	}

	void FileHandler::addAnimation(tinyxml2::XMLElement* anims_tag, Animation* anim) {
		auto anim_tag = m_doc->NewElement("animation");
		anims_tag->InsertEndChild(anim_tag);
		anim_tag->SetAttribute("name", anim->getName().c_str());
		anim_tag->SetAttribute("id", anim->getId());

		auto prop = m_doc->NewElement("properties");
		anim_tag->InsertEndChild(prop);
		prop->SetAttribute("time_length", anim->getTimeLength());
		prop->SetAttribute("loop", anim->isLoop());
		prop->SetAttribute("reverse", anim->isReverse());

		if (anim->getSpriteFrameTrack()) {
			auto sprite_frame_track_tag = m_doc->NewElement("sprite_frame_track");
			anim_tag->InsertEndChild(sprite_frame_track_tag);
			for (auto key : anim->getSpriteFrameTrack()->getKeys()) {
				auto key_tag = m_doc->NewElement("key");
				sprite_frame_track_tag->InsertEndChild(key_tag);
				key_tag->SetAttribute("time", key.time);
				key_tag->SetAttribute("frame", key.data.sprite_frame);
			}
		}
		if (anim->getPositionTrack()) {
			auto position_track_tag = m_doc->NewElement("position_track");
			anim_tag->InsertEndChild(position_track_tag);
			for (auto key : anim->getPositionTrack()->getKeys()) {
				auto key_tag = m_doc->NewElement("key");
				position_track_tag->InsertEndChild(key_tag);
				key_tag->SetAttribute("time", key.time);
				key_tag->SetAttribute("x", key.data.position.x);
				key_tag->SetAttribute("y", key.data.position.y);
			}
		}
		if (anim->getRotationTrack()) {
			auto rotation_track_tag = m_doc->NewElement("rotation_track");
			anim_tag->InsertEndChild(rotation_track_tag);
			for (auto key : anim->getRotationTrack()->getKeys()) {
				auto key_tag = m_doc->NewElement("key");
				rotation_track_tag->InsertEndChild(key_tag);
				key_tag->SetAttribute("time", key.time);
				key_tag->SetAttribute("angle", key.data.rotation);
			}
		}
		if (anim->getScaleTrack()) {
			auto scale_track_tag = m_doc->NewElement("scale_track");
			anim_tag->InsertEndChild(scale_track_tag);
			for (auto key : anim->getScaleTrack()->getKeys()) {
				auto key_tag = m_doc->NewElement("key");
				scale_track_tag->InsertEndChild(key_tag);
				key_tag->SetAttribute("time", key.time);
				key_tag->SetAttribute("x", key.data.scale.x);
				key_tag->SetAttribute("y", key.data.scale.y);
			}
		}
	}
	
}