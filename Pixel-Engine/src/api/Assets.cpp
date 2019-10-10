#include "pch.h"
#include "Assets.h"

namespace pe
{
	std::map<std::string, construct_f> Assets::s_object_registry;
	std::vector<std::string> Assets::s_pyobj_paths;
	std::map<int, Asset*>	Assets::s_assets;

	void Assets::assetsDistruct() { // TODO: add remove(any asset) functions
		for (auto asset : s_assets) delete asset.second;
	}

	// setters
	void Assets::addAsset(Asset* asset) {
		if (hasAsset(asset->getId())) delete s_assets[asset->getId()];
		s_assets[asset->getId()] = asset;
	}

	bool Assets::hasAsset(const std::string& name) {
		for (auto asset : s_assets) { if (asset.second->getName() == name) return true; }
		return false;
	}

	bool Assets::hasAsset(int id) {
		return s_assets.find(id) != s_assets.end();
	}

	bool Assets::isClassRegistered(const std::string& class_name) {
		auto pair = s_object_registry.find(class_name);
		return pair != s_object_registry.end();
	}

	Object* Assets::newObject(const std::string& class_name) {
		auto pair = s_object_registry.find(class_name);
		assert( pair != s_object_registry.end() && "unregistered class_name to construct use REGISTER_CLASS macro to register your classes" );
		Object* obj = pair->second(class_name);
		addAsset(obj);
		return obj;
	}
	Object* Assets::newObject(int id) {
		if (hasAsset(id)) deleteAsset(id);
		Object* obj = new pe::Object(id);
		addAsset(obj);
		return obj;
	}
	Scene* Assets::newScene(int id) {
		Scene* scn = new pe::Scene(id);
		addAsset(scn);
		return scn;
	}

}