#include "pch.h"
#include "assets_window.h"
#include "globals.h"

void AssetsWindow::init(){}

void AssetsWindow::renderAssetsWindow()
{
	ImGui::Begin("Assets");
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("Assets")) {
		

		

		ImGui::TreePop();
	}

	if (ImGui::Button("save")) {
		/*
		pe::AssetsWriter w;
		w.addAssets(pe::Assets::s_assets);
		w.save( (Globals::s_working_dir  + std::string("assets.xml") ).c_str() );
		*/
	}

	ImGui::End();
}

///////////////////////////////// functions
