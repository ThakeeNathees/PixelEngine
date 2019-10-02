#pragma once
#include "core.h"
#include "Scene.h"


typedef pe::Object* (*construct_f)(const std::string&);
#define REGISTER_CLASS(class_name) pe::Assets::registerClass<class_name>(#class_name)
#define ADD_PYOBJECT_PATH( path ) pe::Assets::addPyobjectPath(path);

namespace pe
{
	
	
	class PIXEL_ENGINE_API Assets
	{
	public:
		static void assetsDistruct();

		// old
		template <typename T>
		static T* newAsset() { Asset* asset = new T(); addAsset(asset); return static_cast<T*>(asset); }
		template <typename T>
		static T* newAsset(const std::string& name) { Asset* asset = new T(name); addAsset(asset); return static_cast<T*>(asset); }
		static Object* newObject(const std::string& class_name);
		static Object* newObject();


		// class register
		template <typename T> // function to store in register map
		static pe::Object* construct(const std::string& class_name) {
			pe::Object* obj = static_cast<pe::Object*>(new T());
			obj->m_class_name = class_name;
			return obj;
		}

		template <typename T>
		static void registerClass(const std::string& class_name) {
			s_object_registry[class_name] = &construct<T>;
		}

		static void addPyobjectPath(const std::string& path) {s_pyobj_paths.push_back(path);}
		static const std::vector<std::string>& getPyobjectPaths() { return s_pyobj_paths; }
		// setters
		static void addAsset(Asset* asset);



		// getters
		static bool hasAsset(const std::string& name);
		static bool hasAsset(int id);

		template <typename T>
		static T* getAsset(const std::string& name){
			for (auto asset : s_assets) if (asset.second->getName() == name) return static_cast<T*>(asset.second);
			return nullptr;
		}

		template <typename T>
		static T* getAsset(int id) {
			if(! hasAsset(id)) return nullptr;
			return static_cast<T*>(s_assets[id]);
		}
		
		// TODO: delete queue, add text, object, scene, tilemap
		// TODO: and remove s_assets with id, ...

	private:
		friend class FileHandler;
	
		static std::map<int, Asset*> s_assets;

		static std::vector<std::string> s_pyobj_paths;
		static std::map<std::string, construct_f> s_object_registry;
		static std::vector<std::string> s_python_classes;

		// debug
		friend class Application;
	};
}