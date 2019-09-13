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

		// if success return 0
		int writeProject(const struct _peproj& proj, const char* path);
		int writeObject(Object* obj, const char* path); // path to folder with '/' , file name = name of obj_id
		int writeScene(Scene* scene, const char* path);

		int readProject(const char* path);
		_peproj& getProject() { return m_peproj; }
		int readAssets(const char* path);
		void readObject(const char* path, Application* app);
		void readScenes(const char* path, Application* app);


	private:
		void setSprite(tinyxml2::XMLElement* obj_tag, Sprite& sprite);
		void setArea(tinyxml2::XMLElement* obj_tag, Area& area);
		void addAnimation(tinyxml2::XMLElement* obj_tag, Animation* anim);
		tinyxml2::XMLDocument* m_doc = nullptr;
		_peproj m_peproj;
	};
}
