#include "pch.h"
#include "FileHandler.h"


#include "tinyxml2.h"
#include "bindings/python/PythonObject.h"

namespace pe
{
	int FileHandler::readProject(const char* path) {
		int error = m_doc->LoadFile(path);
		if (error) return error;
		auto root = m_doc->FirstChildElement("Project");
		m_peproj.title = root->Attribute("title");

		auto size_tag = root->FirstChildElement("window_size");
		m_peproj.window_size.x = size_tag->IntAttribute("x");
		m_peproj.window_size.y = size_tag->IntAttribute("y");

		auto pref_tag = root->FirstChildElement("pref");
		m_peproj.frame_rate = pref_tag->IntAttribute("frame_rate");
		m_peproj.begin_scene_id = pref_tag->IntAttribute("begin_scene_id");
		m_peproj.is_debug_mode = pref_tag->BoolAttribute("debug_mode");
		auto s = pref_tag->BoolAttribute("no_console");
		m_peproj.no_console_window = pref_tag->BoolAttribute("no_console");

		if (auto logo_texture_tag = root->FirstChildElement("logo_texture")) {
			m_peproj.logo_texture_id = logo_texture_tag->IntAttribute("id");
		}
		else {
			m_peproj.logo_texture_id = -1;
		}


		auto bg_color_tag = root->FirstChildElement("bg_color");
		m_peproj.default_bg_color.r = bg_color_tag->IntAttribute("r");
		m_peproj.default_bg_color.g = bg_color_tag->IntAttribute("g");
		m_peproj.default_bg_color.b = bg_color_tag->IntAttribute("b");
		m_peproj.default_bg_color.a = bg_color_tag->IntAttribute("a");

		auto assets_tag = root->FirstChildElement("assets");
		m_peproj.assets_path = assets_tag->GetText();

		auto objects_tag = root->FirstChildElement("objects");
		for (auto path_tag = objects_tag->FirstChildElement(); path_tag != NULL; path_tag = path_tag->NextSiblingElement()) {
			m_peproj.objects_path.push_back(path_tag->GetText());
		}

		auto scenes_tag = root->FirstChildElement("scenes");
		for (auto path_tag = scenes_tag->FirstChildElement(); path_tag != NULL; path_tag = path_tag->NextSiblingElement()) {
			m_peproj.scene_paths.push_back(path_tag->GetText());
		}
		return error; // 0 means success
	} // project

	int FileHandler::readAssets(const char* path) {
		int error = m_doc->LoadFile(path);
		if (error) return error;

		auto textures = m_doc->FirstChildElement()->FirstChildElement("textures");
		Texture::s_next_id = textures->IntAttribute("next_id");
		for (auto texture_tag = textures->FirstChildElement(); texture_tag != NULL; texture_tag = texture_tag->NextSiblingElement()) {
			Texture* texture = new Texture();
			texture->setName(texture_tag->Attribute("name"));
			texture->m_id = texture_tag->IntAttribute("id");
			texture->setSmooth(texture_tag->BoolAttribute("smooth"));
			texture->setRepeated(texture_tag->BoolAttribute("repeat"));
			std::string  path = texture_tag->GetText();
			texture->loadFromFile(path);
			Assets::s_assets[texture->m_id] = texture;
		}

		auto fonts = m_doc->FirstChildElement()->FirstChildElement("fonts");
		for (auto font_tag = fonts->FirstChildElement(); font_tag != NULL; font_tag = font_tag->NextSiblingElement()) {
			Font* font = new Font();
			font->setName(font_tag->Attribute("name"));
			font->m_id = font_tag->IntAttribute("id");
			Font::s_next_id = glm::max(font->m_id + 1, Font::s_next_id);
			std::string path = font_tag->GetText();
			font->loadFromFile(path);
			if (!Text::getDefaultFont()) Text::setDefaultFont(font);
			Assets::s_assets[font->m_id] = font;
		}

		return error;
	} // assets

	void FileHandler::readObject(const char* path, Application* app) {
		m_doc->LoadFile(path);
		auto obj_tag = m_doc->FirstChildElement("object");

		std::string type = obj_tag->Attribute("type");
		std::string class_name = obj_tag->Attribute("class_name");

		Object* obj = nullptr;
		if (type == std::string("CPP_OBJECT"))
			obj = Assets::newObject(class_name); // TODO: assert here
		else if (type == std::string("PYTHON_OBJECT")) {
			obj = new PythonObject(class_name);
			Assets::addAsset(obj);
		}

		obj->setName(obj_tag->Attribute("name"));
		obj->m_id = obj_tag->IntAttribute("id");
		Object::s_next_id = glm::max(obj->m_id + 1, Object::s_next_id);

		auto prop = obj_tag->FirstChildElement("properties");
		obj->setVisible(prop->BoolAttribute("visible"));
		obj->setZindex(prop->IntAttribute("z_index"));
		obj->setPersistence(prop->BoolAttribute("persistence"));

		auto transform_tag = obj_tag->FirstChildElement("transform");
		auto pos_tag = transform_tag->FirstChildElement("position");
		obj->setPosition(pos_tag->FloatAttribute("x"), pos_tag->FloatAttribute("y"));
		auto rotation_tag = transform_tag->FirstChildElement("rotation");
		obj->setRotation(rotation_tag->FloatAttribute("angle"));
		auto scale_tag = transform_tag->FirstChildElement("scale");
		obj->setScale(scale_tag->FloatAttribute("x"), scale_tag->FloatAttribute("y"));
		auto origin_tag = transform_tag->FirstChildElement("origin");
		obj->setOrigin(origin_tag->FloatAttribute("x"), origin_tag->FloatAttribute("y"));

		auto spr_tag = obj_tag->FirstChildElement("sprite");
		if (spr_tag) {
			Sprite* sprite = new Sprite();
			sprite->setName(spr_tag->Attribute("name"));
			sprite->m_id = spr_tag->IntAttribute("id");

			auto tex_tag = spr_tag->FirstChildElement("texture");
			if (tex_tag) {
				int id = tex_tag->IntAttribute("id");
				Sprite::s_next_id = glm::max(sprite->m_id + 1, Sprite::s_next_id);
				assert(Assets::s_assets[id] != NULL && "can't find texture for the sprite");
				sprite->setTexture(*dynamic_cast<Texture*>(Assets::s_assets[id]));

				sf::IntRect rect;
				rect.left = spr_tag->FirstChildElement("texture_rect")->IntAttribute("left");
				rect.top = spr_tag->FirstChildElement("texture_rect")->IntAttribute("top");
				rect.width = spr_tag->FirstChildElement("texture_rect")->IntAttribute("width");
				rect.height = spr_tag->FirstChildElement("texture_rect")->IntAttribute("height");
				sprite->setTextureRect(rect);

				std::tuple<sf::Vector2i, sf::Vector2i> frames;
				sf::Vector2i dimension, offset;
				dimension.x = spr_tag->FirstChildElement("frames")->IntAttribute("x");
				dimension.y = spr_tag->FirstChildElement("frames")->IntAttribute("y");
				offset.x = spr_tag->FirstChildElement("frames")->IntAttribute("offset_x");
				offset.y = spr_tag->FirstChildElement("frames")->IntAttribute("offset_y");
				int index = spr_tag->FirstChildElement("frames")->IntAttribute("index");
				auto tup = std::make_tuple(dimension, offset);
				sprite->setFrames(tup);
				sprite->setFrameIndex(index);
			}
			obj->setSprite(sprite);
			Assets::s_assets[sprite->m_id] = sprite;
		} // sprite

		auto area_tag = obj_tag->FirstChildElement("area");
		if (area_tag) {
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
			obj->setArea(area);
			Assets::s_assets[area->m_id] = area;
		} // area

		auto anims_tag = obj_tag->FirstChildElement("animations");
		for (auto anim_tag = anims_tag->FirstChildElement(); anim_tag != NULL; anim_tag = anim_tag->NextSiblingElement()) {
			Animation* anim = new Animation();
			anim->setName(anim_tag->Attribute("name"));
			anim->m_id = anim_tag->IntAttribute("id");
			Animation::s_next_id = glm::max(anim->m_id + 1, Animation::s_next_id);

			auto prop_tag = anim_tag->FirstChildElement("properties");
			anim->setTimeLength(prop_tag->FloatAttribute("time_length"));
			anim->setLoop(prop_tag->BoolAttribute("loop"));
			anim->setReverse(prop_tag->BoolAttribute("reverse"));

			anim->m_object_id = obj->getId();

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
			obj->addAnimation(anim);
			Assets::s_assets[anim->m_id] = anim;
		} // animation
		Assets::s_assets[obj->m_id] = obj;
		if (app && obj->isPersistence()) app->addPersistenceObject(obj);

	} // objects

	void FileHandler::readScenes(const char* path, Application* app) {
		m_doc->LoadFile(path);
		auto scn_tag = m_doc->FirstChildElement("scene");

		Scene* scene = Assets::newAsset<Scene>();
		scene->setName(scn_tag->Attribute("name"));
		scene->m_id = scn_tag->IntAttribute("id");
		Scene::s_next_id = glm::max(scene->m_id + 1, Scene::s_next_id);

		auto bg_tag = scn_tag->FirstChildElement("background");
		if (bg_tag) {
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
				assert(Assets::s_assets[id] != NULL && "can't find texture for the background");
				bg->setTexture(*dynamic_cast<Texture*>(Assets::s_assets[id]));
				bg->setSmooth(bg_tag->FirstChildElement("properties")->BoolAttribute("smooth"));
			}
			Assets::s_assets[bg->m_id] = bg;
		} // bg

		auto objs_tag = scn_tag->FirstChildElement("objects");
		for (auto obj_tag = objs_tag->FirstChildElement(); obj_tag != NULL; obj_tag = obj_tag->NextSiblingElement()) {
			int id = obj_tag->IntAttribute("id");
			assert(Assets::s_assets[id] != NULL && "can't find the object for the scene");
			scene->addObject(dynamic_cast<Object*>(Assets::s_assets[id]));
		}
		Assets::s_assets[scene->m_id] = scene;
		if (app) app->addScene(scene);
	} // scenes
}