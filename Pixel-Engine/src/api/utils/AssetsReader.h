#pragma once
#include "..//core.h"

#include "..//Application.h"


namespace tinyxml2 { class XMLDocument; }

namespace pe
{
	class Assets;

	class PIXEL_ENGINE_API AssetsReader
	{
	public:

		AssetsReader(const char* path);
		AssetsReader();
		void loadFile(const char* path);
		void readAssets(Application* app=nullptr);
		void readAssets(std::map<int, Asset*>& asset_map, Application* app = nullptr);
		void printDoc() const;

		void _readPeproj();
		inline const struct _peproj& _getPeproj() { return m_peproj; }

	private:

		void readTextures(std::map<int, Asset*>& asset_map);
		void readFonts(std::map<int, Asset*>& asset_map);
		void readArea(std::map<int, Asset*>& asset_map);
		void readSprites(std::map<int, Asset*>& asset_map);
		void readBackground(std::map<int, Asset*>& asset_map);
		void readAnimation(std::map<int, Asset*>& asset_map);
		void readObject(std::map<int, Asset*>& asset_map, Application* app = nullptr);
		void readScene(std::map<int, Asset*>& asset_map, Application* app=nullptr);


		tinyxml2::XMLDocument* m_doc;
		struct _peproj m_peproj;
	};
}