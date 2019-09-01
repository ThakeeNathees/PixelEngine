#pragma once
#include "..//core.h"

#include "..//Scene.h"
#include "..//misc/Texture.h"
#include "..//misc/Font.h"


namespace tinyxml2 { class XMLDocument; }

namespace pe
{
	class Assets;

	class PIXEL_ENGINE_API AssetsReader
	{
	public:
		AssetsReader(const char* path);
		void loadFile(const char* path);
		void readAssets();
		void readAssets(std::map<int, Asset*>& asset_map);
		void printDoc() const;

	private:

		void readTextures(std::map<int, Asset*>& asset_map);
		void readFonts(std::map<int, Asset*>& asset_map);
		void readArea(std::map<int, Asset*>& asset_map);
		void readSprites(std::map<int, Asset*>& asset_map);
		void readBackground(std::map<int, Asset*>& asset_map);
		void readAnimation(std::map<int, Asset*>& asset_map);

		tinyxml2::XMLDocument* m_doc;
	};
}