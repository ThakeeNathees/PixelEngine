#pragma once
#include "../core.h"

#include "..//Application.h"

namespace tinyxml2 { class XMLDocument; class XMLElement; }

namespace pe
{

	class PIXEL_ENGINE_API FileHandler
	{
	public:
		FileHandler();

		void writeProject(const struct _peproj& proj, const char* path);
		void writeObject(Object* obj, const char* path); // path to folder with '/' , file name = name of obj_id
		void writeScene(Scene* scene, const char* path);
		/*
		// writer
		*/

		/*
		// reader
		void readProject(const char* path, Application* app);
		void readAssets(const char* path); // read font and textures to Assets::s_fonts, s_textures
		void readObject(const char* path);
		void readScene(const char* path);
		*/

	private:
		void setSprite(tinyxml2::XMLElement* obj_tag, Sprite& sprite);
		void setArea(tinyxml2::XMLElement* obj_tag, Area& area);
		void addAnimation(tinyxml2::XMLElement* obj_tag, Animation* anim);
		tinyxml2::XMLDocument* m_doc = nullptr;
	};
}
