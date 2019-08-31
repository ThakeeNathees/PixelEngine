#pragma once
#include "core.h"

#include "entities/Sprite.h"
#include "entities/Background.h"
#include "entities/Animation.h"
#include "entities/Area.h"

#include "misc/Texture.h"
#include "misc/Font.h"

#include "utils/AssetsWriter.h"

/*
assets (fonts, areas, aprites, ...) are static to class Assets
to organize and save the assets they group together as packets.
*/

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
		


		// setters
		static void addAsset(Asset* asset);

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

	private:
		friend class AssetsReader;
		friend class AssetsWriter;
		friend class AssetsWindow;
		static std::map<int, Asset*> s_assets;
	};
}