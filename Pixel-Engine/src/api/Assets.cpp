#include "pch.h"
#include "Assets.h"

namespace pe
{
	std::map<std::string, construct_f> Assets::s_object_registry;

	std::map<int, Asset*>	Assets::s_assets;

	void Assets::assetsDistruct() { // TODO: add remove(any asset) functions
		for (auto asset : s_assets) delete asset.second;
	}

	// setters
	void Assets::addAsset(Asset* asset) {
		if (hasAsset(asset->getId())) return;
		s_assets[asset->getId()] = asset;
	}

	bool Assets::hasAsset(const std::string& name) {
		for (auto asset : s_assets) { if (asset.second->getName() == name) return true; }
		return false;
	}

	bool Assets::hasAsset(int id) {
		return s_assets.find(id) != s_assets.end();
	}

	Object* Assets::newObject(const std::string& class_name) {
		auto pair = s_object_registry.find(class_name);
		assert( pair != s_object_registry.end() && "unregistered class_name to construct use REGISTER_CLASS macro to register your classes" );
		Object* obj = pair->second(class_name);
		// old
		addAsset(obj);
		return obj;
	}
	/*
	*/
	
}