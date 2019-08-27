#include "pch.h"
#include "AssetsWriter.h"



namespace pe
{
	AssetsWriter::AssetsWriter() {
		auto assets = m_doc.NewElement("assets");
		m_doc.InsertFirstChild(assets);

		auto textures		= m_doc.NewElement("textures");
		auto fonts			= m_doc.NewElement("fonts");
		auto areas			= m_doc.NewElement("areas");
		auto sprites		= m_doc.NewElement("sprites");
		auto backgrounds	= m_doc.NewElement("backgrounds");
		auto animations		= m_doc.NewElement("animations");
		// tile map, ...

		assets->InsertEndChild(textures);
		assets->InsertEndChild(fonts);
		assets->InsertEndChild(areas);
		assets->InsertEndChild(sprites);
		assets->InsertEndChild(backgrounds);
		assets->InsertEndChild(animations);
	}

	void AssetsWriter::addTexture(Texture* texture) {
		auto textures = m_doc.FirstChildElement()->FirstChildElement("textures");
		auto texture_tag = m_doc.NewElement("texture");
		textures->InsertEndChild(texture_tag);
		texture_tag->SetAttribute("name", texture->getName().c_str());
		texture_tag->SetAttribute("id", texture->getId());
		texture_tag->SetAttribute("smooth", texture->isSmooth());
		texture_tag->SetAttribute("repeat", texture->isRepeated());
		texture_tag->SetText(texture->getPath().c_str());
	}

	void AssetsWriter::addFont(Font* font) {
		auto fonts = m_doc.FirstChildElement()->FirstChildElement("fonts");
		auto font_tag = m_doc.NewElement("font");
		fonts->InsertEndChild(font_tag);
		font_tag->SetAttribute("name", font->getName().c_str());
		font_tag->SetAttribute("id", font->getId());
		font_tag->SetText(font->getPath().c_str());
	}

	void AssetsWriter::addArea(Area* area) {
		auto areas = m_doc.FirstChildElement()->FirstChildElement("areas");
		auto area_tag = m_doc.NewElement("area");
		areas->InsertEndChild(area_tag);
		area_tag->SetAttribute("name", area->getName().c_str());
		area_tag->SetAttribute("id", area->getId());

		if (area->hasShape()) {
			if (area->hasShape()) {
				auto shape_tag = m_doc.NewElement("shape");
				area_tag->InsertEndChild(shape_tag);
				shape_tag->SetAttribute("point_count", (int)area->getPointCount());
				for (int i = 0; i < area->getPointCount(); i++) {
					auto point_tag = m_doc.NewElement("point");
					shape_tag->InsertEndChild(point_tag);
					point_tag->SetAttribute("index", i);
					point_tag->SetAttribute("x", area->getShape().getPoint(i).x);
					point_tag->SetAttribute("y", area->getShape().getPoint(i).y);
				}
			}
		}
	}

	void AssetsWriter::addSprite(Sprite* sprite) {
		auto sprites = m_doc.FirstChildElement()->FirstChildElement("sprites");
		auto sprite_tag = m_doc.NewElement("sprite");
		sprites->InsertEndChild(sprite_tag);
		sprite_tag->SetAttribute("name", sprite->getName().c_str());
		sprite_tag->SetAttribute("id", sprite->getId());

		
		if (sprite->hasTexture()) {
			auto texture_tag = m_doc.NewElement("texture");
			sprite_tag->InsertEndChild(texture_tag);
			texture_tag->SetAttribute("id", sprite->getTexture().getId());

			auto texture_rect_tag = m_doc.NewElement("texture_rect");
			sprite_tag->InsertEndChild(texture_rect_tag);
			texture_rect_tag->SetAttribute("left", sprite->getTextureRect().left);
			texture_rect_tag->SetAttribute("top", sprite->getTextureRect().top);
			texture_rect_tag->SetAttribute("width", sprite->getTextureRect().width);
			texture_rect_tag->SetAttribute("height", sprite->getTextureRect().height);

			auto frames_tag = m_doc.NewElement("frames");
			sprite_tag->InsertEndChild(frames_tag);
			frames_tag->SetAttribute("x", sprite->getFrames().x);
			frames_tag->SetAttribute("y", sprite->getFrames().y);
			frames_tag->SetAttribute("offset_x", sprite->getFrames().z);
			frames_tag->SetAttribute("offset_y", sprite->getFrames().w);
			frames_tag->SetAttribute("index", sprite->getFrameIndex());
		}
	}


	void AssetsWriter::addBackground(Background* bg) {
		auto bgs = m_doc.FirstChildElement()->FirstChildElement("backgrounds");
		auto bg_tag = m_doc.NewElement("background");
		bgs->InsertEndChild(bg_tag);
		bg_tag->SetAttribute("name", bg->getName().c_str());
		bg_tag->SetAttribute("id", bg->getId());
		

		auto prop = m_doc.NewElement("properties");
		bg_tag->InsertEndChild(prop);
		prop->SetAttribute("visible", bg->getVisible());
		prop->SetAttribute("repeat", bg->getRepeat());
		prop->SetAttribute("smooth", bg->getSmooth());

		auto speed_tag = m_doc.NewElement("move_speed");
		bg_tag->InsertEndChild(speed_tag);
		speed_tag->SetAttribute("x", bg->getMoveSpeed().x);
		speed_tag->SetAttribute("y", bg->getMoveSpeed().y);

		auto scale_tag = m_doc.NewElement("scale");
		bg_tag->InsertEndChild(scale_tag);
		scale_tag->SetAttribute("x", bg->getScale().x);
		scale_tag->SetAttribute("y", bg->getScale().y);

		if (bg->hasTexture()) {
			auto texture_tag = m_doc.NewElement("texture");
			bg_tag->InsertEndChild(texture_tag);
			texture_tag->SetAttribute("id", bg->getTexture().getId());
		}
	}

	void AssetsWriter::addAnimation(Animation* anim) {
		auto anims = m_doc.FirstChildElement()->FirstChildElement("animations");
		auto anim_tag = m_doc.NewElement("animation");
		anims->InsertEndChild(anim_tag);
		anim_tag->SetAttribute("name", anim->getName().c_str());
		anim_tag->SetAttribute("id", anim->getId());

		auto prop = m_doc.NewElement("properties");
		anim_tag->InsertEndChild(prop);
		prop->SetAttribute("time_length", anim->getTimeLength());
		prop->SetAttribute("loop", anim->getLoop());
		prop->SetAttribute("reverse", anim->getReverse());

		if (anim->hasObject()) {
			auto obj_tag = m_doc.NewElement("object");
			anim_tag->InsertEndChild(obj_tag);
			obj_tag->SetAttribute("id", anim->getObject().getId());
		}

		auto begin_transform_tag = m_doc.NewElement("begin_transform");
		anim_tag->InsertEndChild(begin_transform_tag);
		auto begin_pos_tag = m_doc.NewElement("position");
		begin_transform_tag->InsertEndChild(begin_pos_tag);
		begin_pos_tag->SetAttribute("x", anim->getBeginPosition().x);
		begin_pos_tag->SetAttribute("y", anim->getBeginPosition().y);
		auto begin_rotation_tag = m_doc.NewElement("rotation");
		begin_transform_tag->InsertEndChild(begin_rotation_tag);
		begin_rotation_tag->SetAttribute("angle", anim->getBeginRotation());
		auto begin_scale_tag = m_doc.NewElement("scale");
		begin_transform_tag->InsertEndChild(begin_scale_tag);
		begin_scale_tag->SetAttribute("x", anim->getBeginScale().x);
		begin_scale_tag->SetAttribute("y", anim->getBeginScale().y);
		
		if (anim->hasSpriteFrameTrack()) {
			auto sprite_frame_track_tag = m_doc.NewElement("sprite_frame_track");
			anim_tag->InsertEndChild(sprite_frame_track_tag);
			for (auto key : anim->getSpriteFrameTrack().getKeys()) {
				auto key_tag = m_doc.NewElement("key");
				sprite_frame_track_tag->InsertEndChild(key_tag);
				key_tag->SetAttribute("time", key.time);
				key_tag->SetAttribute("frame", key.data.sprite_frame);
			}
		}
		if (anim->hasPositionTrack()) {
			auto position_track_tag = m_doc.NewElement("position_frame_track");
			anim_tag->InsertEndChild(position_track_tag);
			for (auto key : anim->getPositionTrack().getKeys()) {
				auto key_tag = m_doc.NewElement("key");
				position_track_tag->InsertEndChild(key_tag);
				key_tag->SetAttribute("time", key.time);
				key_tag->SetAttribute("frame", key.data.sprite_frame);
			}
		}
		if (anim->hasRotationTrack()) {
			auto rotation_track_tag = m_doc.NewElement("rotation_frame_track");
			anim_tag->InsertEndChild(rotation_track_tag);
			for (auto key : anim->getPositionTrack().getKeys()) {
				auto key_tag = m_doc.NewElement("key");
				rotation_track_tag->InsertEndChild(key_tag);
				key_tag->SetAttribute("time", key.time);
				key_tag->SetAttribute("frame", key.data.sprite_frame);
			}
		}
		if (anim->hasScaleTrack()) {
			auto scale_track_tag = m_doc.NewElement("scale_frame_track");
			anim_tag->InsertEndChild(scale_track_tag);
			for (auto key : anim->getPositionTrack().getKeys()) {
				auto key_tag = m_doc.NewElement("key");
				scale_track_tag->InsertEndChild(key_tag);
				key_tag->SetAttribute("time", key.time);
				key_tag->SetAttribute("frame", key.data.sprite_frame);
			}
		}
	}

	

}