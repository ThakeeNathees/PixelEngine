#pragma once
#include "core.h"
#include "Scene.h"


/*
assets (fonts, areas, aprites, ...) are static to class Assets
to organize and save the assets they group together as m_assets in each Assets instance.
*/




typedef pe::Object* (*construct_f)(const std::string&);
#define REGISTER_CLASS(class_name) pe::Assets::registerClass<class_name>(#class_name);

namespace pe
{
	
	
	class PIXEL_ENGINE_API Assets
	{
	public:
		static void assetsDistruct();

		template <typename T>
		static T* newAsset() { Asset* asset = new T(); addAsset(asset); return static_cast<T*>(asset); }

		template <typename T>
		static T* newAsset(const std::string& name) { Asset* asset = new T(name); addAsset(asset); return static_cast<T*>(asset); }
		

		// class register
		template <typename T>
		static pe::Object* construct(const std::string& class_name) {
			pe::Object* obj = static_cast<pe::Object*>(new T());
			obj->m_class_name = class_name;
			return obj;
		}

		template <typename T>
		static void registerClass(const std::string& class_name) {
			s_object_registry[class_name] = &construct<T>;
		}
		static Object* constructObj(const std::string& class_name);

		// setters
		static void addAsset(Asset* asset);
		void addAsset(int id);
		void removeAsset(int id);


		// getters
		static bool hasAsset(const std::string& name);
		static bool hasAsset(int id);

		template <typename T>
		static T* getAsset(const std::string& name){
			for (auto asset : s_assets) if (asset.second->getName() == name) return static_cast<T*>(asset.second);
			assert(false && "invalid asset name to get!");
		}

		template <typename T>
		static T* getAsset(int id) {
			assert( hasAsset(id) && "invalid asset name to get!");
			return static_cast<T*>(s_assets[id]);
		}
		
		// TODO: delete queue, add text, object, scene, tilemap
		// TODO: and remove s_assets with id, ...

	private:
		friend class AssetsReader;
		friend class AssetsWriter;
		friend class AssetsWindow; // delete this line
		static std::map<int, Asset*> s_assets;
		std::vector<int> m_assets;

		static std::map<std::string, construct_f> s_object_registry;
	};
}