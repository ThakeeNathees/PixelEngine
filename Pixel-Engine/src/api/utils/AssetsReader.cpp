#include "pch.h"
#include "AssetsReader.h"

#include "tinyxml2.h"
#include "..//Assets.h"

namespace pe
{

	AssetsReader::AssetsReader(const char* path) {
		m_doc = new tinyxml2::XMLDocument();
		m_doc->LoadFile(path);
	}
	void AssetsReader::loadFile(const char* path) { m_doc->LoadFile(path); }

	void AssetsReader::printDoc() const {
		m_doc->Print();
	}

	void AssetsReader::readAssets(std::map<int, Asset*>& asset_map, Application* app){
		readTextures( asset_map );
		readFonts(asset_map);
		readArea(asset_map);
		readSprites(asset_map);
		readBackground(asset_map);
		readAnimation(asset_map);
		readObject(asset_map, app);
		readScene(asset_map, app);
	}
	void AssetsReader::readAssets(Application* app) {
		readAssets(Assets::s_assets, app);
	}

	void AssetsReader::readTextures(std::map<int, Asset*>& asset_map) {
		auto textures = m_doc->FirstChildElement()->FirstChildElement("textures");
		for (auto texture_tag = textures->FirstChildElement(); texture_tag != NULL; texture_tag = texture_tag->NextSiblingElement()) {
			Texture* texture = new Texture();
			texture->setName(texture_tag->Attribute("name") );
			texture->m_id = texture_tag->IntAttribute("id"); // TODO: change this to assert line -> m_id == attr("id")
			Texture::s_next_id = glm::max(texture->m_id + 1, Texture::s_next_id);
			texture->setSmooth(texture_tag->BoolAttribute("smooth") );
			texture->setRepeated(texture_tag->BoolAttribute("repeat") );
			std::string  path = texture_tag->GetText();
			if (path != "") {
				texture->loadFromFile(path);
			}
			asset_map[texture->m_id] = texture;
			Assets::s_assets[texture->m_id] = texture;
		}
	}

	void AssetsReader::readFonts(std::map<int, Asset*>& asset_map) {
		auto fonts = m_doc->FirstChildElement()->FirstChildElement("fonts");
		for (auto font_tag = fonts->FirstChildElement(); font_tag != NULL; font_tag = font_tag->NextSiblingElement()) {
			Font* font = new Font();
			font->setName(font_tag->Attribute("name"));
			font->m_id = font_tag->IntAttribute("id");
			Font::s_next_id = glm::max(font->m_id + 1, Font::s_next_id);
			std::string path = font_tag->GetText();
			if (path != "") {
				font->loadFromFile(path);
			}
			asset_map[font->m_id] = font;
			Assets::s_assets[font->m_id] = font;
		}
	}

	void AssetsReader::readArea(std::map<int, Asset*>& asset_map) {
		auto areas = m_doc->FirstChildElement()->FirstChildElement("areas");
		for (auto area_tag = areas->FirstChildElement(); area_tag != NULL; area_tag = area_tag->NextSiblingElement()) {
			Area* area = new Area();
			area->setName(area_tag->Attribute("name"));
			area->m_id = area_tag->IntAttribute("id");
			Area::s_next_id = glm::max(area->m_id + 1, Area::s_next_id);

			auto shape_tag = area_tag->FirstChildElement("shape");
			if (shape_tag) {
				int point_count = shape_tag->IntAttribute("point_count");
				sf::ConvexShape* shape = new sf::ConvexShape(point_count);
				for (auto point_tag = shape_tag->FirstChildElement(); point_tag != NULL; point_tag = point_tag->NextSiblingElement()) {
					assert(point_tag->IntAttribute("index") < point_count);
					shape->setPoint(
						point_tag->IntAttribute("index"),
						sf::Vector2f(point_tag->FloatAttribute("x"), point_tag->FloatAttribute("y"))
					);
				}
				area->setShape(shape);
			}
			asset_map[area->m_id] = area;
			Assets::s_assets[area->m_id] = area;
		}
	}

	void AssetsReader::readSprites(std::map<int, Asset*>& asset_map) {
		auto sprites = m_doc->FirstChildElement()->FirstChildElement("sprites");
		for (auto spr_tag = sprites->FirstChildElement(); spr_tag!= NULL; spr_tag = spr_tag->NextSiblingElement()) {
			Sprite* sprite = new Sprite();
			sprite->setName(spr_tag->Attribute("name"));
			sprite->m_id = spr_tag->IntAttribute("id");
			
			auto tex_tag = spr_tag->FirstChildElement("texture");
			if (tex_tag) {
				int id = tex_tag->IntAttribute("id");
				Sprite::s_next_id = glm::max(sprite->m_id + 1, Sprite::s_next_id);
				assert( Assets::s_assets[id] != NULL && "can't find texture for the sprite");
				sprite->setTexture( *dynamic_cast<Texture*>(Assets::s_assets[id]) );

				sf::IntRect rect;
				rect.left = spr_tag->FirstChildElement("texture_rect")->IntAttribute("left");
				rect.top = spr_tag->FirstChildElement("texture_rect")->IntAttribute("top");
				rect.width = spr_tag->FirstChildElement("texture_rect")->IntAttribute("width");
				rect.height = spr_tag->FirstChildElement("texture_rect")->IntAttribute("height");
				sprite->setTextureRect(rect);

				glm::ivec4 frames;
				frames.x = spr_tag->FirstChildElement("frames")->IntAttribute("x");
				frames.y = spr_tag->FirstChildElement("frames")->IntAttribute("y");
				frames.z = spr_tag->FirstChildElement("frames")->IntAttribute("offset_x");
				frames.w = spr_tag->FirstChildElement("frames")->IntAttribute("offset_y");
				int index = spr_tag->FirstChildElement("frames")->IntAttribute("index");
				sprite->setFrames(frames);
				sprite->setFrameIndex(index);
			}
			asset_map[sprite->m_id] = sprite;
			Assets::s_assets[sprite->m_id] = sprite;
		}
	}

	void AssetsReader::readBackground(std::map<int, Asset*>& asset_map) {
		auto bgs = m_doc->FirstChildElement()->FirstChildElement("backgrounds");
		for (auto bg_tag = bgs->FirstChildElement(); bg_tag != NULL; bg_tag = bg_tag->NextSiblingElement()) {
			Background* bg = new Background();
			bg->setName(bg_tag->Attribute("name"));
			bg->m_id = bg_tag->IntAttribute("id");
			Background::s_next_id = glm::max(bg->m_id + 1, Background::s_next_id);

			bg->setVisible(bg_tag->FirstChildElement("properties")->BoolAttribute("visible"));
			bg->setMoveSpeed(
				bg_tag->FirstChildElement("move_speed")->IntAttribute("x"),
				bg_tag->FirstChildElement("move_speed")->IntAttribute("y")
			);
			bg->setScale(
				bg_tag->FirstChildElement("scale")->FloatAttribute("x"),
				bg_tag->FirstChildElement("scale")->FloatAttribute("y")
			);

			auto tex_tag = bg_tag->FirstChildElement("texture");
			if (tex_tag) {
				int id = tex_tag->IntAttribute("id");
				assert( Assets::s_assets[id] != NULL && "can't find texture for the background");
				bg->setTexture(*dynamic_cast<Texture*>(Assets::s_assets[id]));
				bg->setSmooth(bg_tag->FirstChildElement("properties")->BoolAttribute("smooth"));
			}
			asset_map[bg->m_id] = bg;
			Assets::s_assets[bg->m_id] = bg;
		}
	}

	void AssetsReader::readAnimation(std::map<int, Asset*>& asset_map) {
		auto bgs = m_doc->FirstChildElement()->FirstChildElement("animations");
		for (auto anim_tag = bgs->FirstChildElement(); anim_tag != NULL; anim_tag = anim_tag->NextSiblingElement()) {
			Animation* anim = new Animation();
			anim->setName( anim_tag->Attribute("name") );
			anim->m_id = anim_tag->IntAttribute("id");
			Animation::s_next_id = glm::max(anim->m_id + 1, Animation::s_next_id);

			auto prop_tag = anim_tag->FirstChildElement("properties");
			anim->setTimeLength( prop_tag->FloatAttribute("time_length") );
			anim->setLoop( prop_tag->BoolAttribute("loop") );
			anim->setReverse( prop_tag->BoolAttribute("reverse") );

			auto obj_tag = anim_tag->FirstChildElement("object");
			if (obj_tag) {
				anim->m_object_id = anim_tag->FirstChildElement("object")->IntAttribute("id");
			}

			auto begin_trans_tag = anim_tag->FirstChildElement("begin_transform");
			anim->m_begin_position = glm::fvec2(
				begin_trans_tag->FirstChildElement("position")->FloatAttribute("x"),
				begin_trans_tag->FirstChildElement("position")->FloatAttribute("y")
			);
			anim->m_begin_rotation = begin_trans_tag->FirstChildElement("rotation")->FloatAttribute("angle");
			anim->m_begin_scale = glm::fvec2(
				begin_trans_tag->FirstChildElement("scale")->FloatAttribute("x"),
				begin_trans_tag->FirstChildElement("scale")->FloatAttribute("y")
			);

			auto sprite_frame_track_tag = anim_tag->FirstChildElement("sprite_frame_track");
			if (sprite_frame_track_tag) {
				SpriteFrameTrack* sprite_frame_track = new SpriteFrameTrack();
				for (auto key_tag = sprite_frame_track_tag->FirstChildElement(); key_tag != NULL; key_tag = key_tag->NextSiblingElement()) {
					Track::Key key;
					key.time = key_tag->FloatAttribute("time");
					key.data.sprite_frame = key_tag->IntAttribute("frame");
					sprite_frame_track->addKey(key);
				}
				anim->setSpriteFrameTrack(sprite_frame_track);
			}

			auto position_track_tag = anim_tag->FirstChildElement("position_track");
			if (position_track_tag) {
				PositionTrack* position_track = new PositionTrack;
				for (auto key_tag = position_track_tag->FirstChildElement(); key_tag != NULL; key_tag = key_tag->NextSiblingElement()) {
					Track::Key key;
					key.time = key_tag->FloatAttribute("time");
					key.data.position.x = key_tag->IntAttribute("x");
					key.data.position.y = key_tag->IntAttribute("y");
					position_track->addKey(key);
				}
				anim->setPositionTrack(position_track);
			}

			auto rotation_track_tag = anim_tag->FirstChildElement("rotation_track");
			if (rotation_track_tag) {
				RotationTrack* rotation_track = new RotationTrack();
				for (auto key_tag = rotation_track_tag->FirstChildElement(); key_tag != NULL; key_tag = key_tag->NextSiblingElement()) {
					Track::Key key;
					key.time = key_tag->FloatAttribute("time");
					key.data.rotation = key_tag->FloatAttribute("angle");
					rotation_track->addKey(key);
				}
				anim->setRotationTrack(rotation_track);
			}

			auto scale_track_tag = anim_tag->FirstChildElement("scale_track");
			if (scale_track_tag) {
				ScaleTrack* scale_track = new ScaleTrack();
				for (auto key_tag = scale_track_tag->FirstChildElement(); key_tag != NULL; key_tag = key_tag->NextSiblingElement()) {
					Track::Key key;
					key.time = key_tag->FloatAttribute("time");
					key.data.scale.x = key_tag->IntAttribute("x");
					key.data.scale.y = key_tag->IntAttribute("y");
					scale_track->addKey(key);
				}
				anim->setScaleTrack(scale_track);
			}
			asset_map[anim->m_id] = anim;
			Assets::s_assets[anim->m_id] = anim;
		}
	}

	void AssetsReader::readObject(std::map<int, Asset*>& asset_map, Application* app) {
		auto objs = m_doc->FirstChildElement()->FirstChildElement("objects");
		for (auto obj_tag = objs->FirstChildElement(); obj_tag != NULL; obj_tag = obj_tag->NextSiblingElement()) {
			std::string class_name = obj_tag->Attribute("class_name");
			Object* obj = Assets::constructObj(class_name); // assert here
			obj->setName(obj_tag->Attribute("name"));
			obj->m_id = obj_tag->IntAttribute("id");
			//obj->m_class_name = class_name; already set
			Object::s_next_id = glm::max(obj->m_id + 1, Object::s_next_id);

			auto prop = obj_tag->FirstChildElement("properties");
			obj->setVisible(prop->BoolAttribute("visible") );
			obj->setZIndex(prop->IntAttribute("z_index"));
			obj->setPersistence( prop->BoolAttribute("persistence") );

			auto transform_tag = obj_tag->FirstChildElement("transform");
			auto pos_tag = transform_tag->FirstChildElement("position");
			obj->setPosition( pos_tag->FloatAttribute("x"), pos_tag->FloatAttribute("y") );
			auto rotation_tag = transform_tag->FirstChildElement("rotation");
			obj->setRotation( rotation_tag->FloatAttribute("angle") );
			auto scale_tag = transform_tag->FirstChildElement("scale");
			obj->setScale( scale_tag->FloatAttribute("x"), scale_tag->FloatAttribute("y") );
			auto origin_tag = transform_tag->FirstChildElement("origin");
			obj->setOrigin( origin_tag->FloatAttribute("x"), origin_tag->FloatAttribute("y") );

			auto sprite_tag = obj_tag->FirstChildElement("sprite");
			if (sprite_tag) {
				int id = sprite_tag->IntAttribute("id");
				assert(Assets::s_assets[id] != NULL && "can't find sprite for the object");
				obj->setSprite( (dynamic_cast<Sprite*>(Assets::s_assets[id])) );
			}
			auto area_tag = obj_tag->FirstChildElement("area");
			if (area_tag) {
				int id = area_tag->IntAttribute("id");
				assert(Assets::s_assets[id] != NULL && "can't find area for the object");
				obj->setArea( dynamic_cast<Area*>(Assets::s_assets[id]) );
			}
			auto anims_tag = obj_tag->FirstChildElement("animations");
			for (auto anim_tag = anims_tag->FirstChildElement(); anim_tag != NULL; anim_tag = anim_tag->NextSiblingElement()) {
				int id = anim_tag->IntAttribute("id");
				assert(Assets::s_assets[id] != NULL && "can't find the animation for the object");
				obj->addAnimation( dynamic_cast<Animation*>( Assets::s_assets[id] ) );
			}
			asset_map[obj->m_id] = obj;
			Assets::s_assets[obj->m_id] = obj;
			if (app && obj->getPersistence()) app->addPersistenceObject(obj);
		}
	}

	void AssetsReader::readScene(std::map<int, Asset*>& asset_map, Application* app) {
		auto scns = m_doc->FirstChildElement()->FirstChildElement("scenes");
		for (auto scn_tag = scns->FirstChildElement(); scn_tag != NULL; scn_tag = scn_tag->NextSiblingElement()) {
			Scene* scene = Assets::newAsset<Scene>();
			scene->setName(scn_tag->Attribute("name"));
			scene->m_id = scn_tag->IntAttribute("id");
			Scene::s_next_id = glm::max(scene->m_id + 1, Scene::s_next_id);
			
			auto size_tag = scn_tag->FirstChildElement("window_size");
			scene->m_window_size = glm::ivec2(
				size_tag->IntAttribute("width"),
				size_tag->IntAttribute("height")
			);

			auto bg_tag = scn_tag->FirstChildElement("background");
			if (bg_tag) {
				int id = bg_tag->IntAttribute("id");
				assert(Assets::s_assets[id] != NULL && "can't find background for the scene");
				scene->setBackground( dynamic_cast<Background*>( Assets::s_assets[id] ) );
			}
			auto objs_tag = scn_tag->FirstChildElement("objects");
			for (auto obj_tag = objs_tag->FirstChildElement(); obj_tag != NULL; obj_tag = obj_tag->NextSiblingElement()) {
				int id = obj_tag->IntAttribute("id");
				assert(Assets::s_assets[id] != NULL && "can't find the object for the scene");
				scene->addObject( dynamic_cast<Object*>(Assets::s_assets[id]));
			}
			asset_map[scene->m_id] = scene;
			Assets::s_assets[scene->m_id] = scene;
			if (app) app->addScene(scene);
		}
	}
}