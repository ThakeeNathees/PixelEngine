#include "pch.h"
#include "FileTree.h"



void FileTree::renderAssetsTree(const std::string& path) {
	long long id = PyUtils::getInstance()->getMathUtil().attr("md5Hash")(path, "long").cast<long long>();
	auto file_name = PyUtils::getInstance()->getOs().attr("path").attr("basename")(path).cast<std::string>();
	file_name = PyUtils::getInstance()->getStrUtil().attr("getFileName")(file_name).cast<std::string>();

	float dir_icon_pos = ImGui::GetCursorPosX();
	if (ImGui::TreeNode(path.c_str(), file_name.c_str())) { // tree begins
		// right click
		if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenuAssets(path, id);

		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::getFileFormatIcon("assets_file"));

		for (auto& asset : pe::Assets::getAssets()) {
			ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

			// texture
			if (asset.second->getType() == pe::Asset::Type::Texture) {
				long long id = PyUtils::getInstance()->getMathUtil().attr("md5Hash")(std::string(path).append(std::to_string(asset.first)), "long").cast<long long>();
				if (m_selected_id == id) node_flags |= ImGuiTreeNodeFlags_Selected;
				ImGui::Image(Resources::getFileFormatIcon("asset_texture")); ImGui::SameLine();
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
				ImGui::TreeNodeEx(std::string(asset.second->getName()).c_str(), node_flags);

				// click node
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
					ImageViewer::getInstance()->openImageViwer(pe::Assets::getAsset<pe::Texture>(asset.second->getId())->getPath());
				}
				if (ImGui::IsItemClicked(0)) m_selected_id = id;
				if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
				if (id == m_selected_menu_id) renderRightMouseMenuTexture(asset.second->getId());

			}// font
			else if (asset.second->getType() == pe::Asset::Type::Font) {
				long long id = PyUtils::getInstance()->getMathUtil().attr("md5Hash")(std::string(path).append(std::to_string(asset.first)), "long").cast<long long>();
				if (m_selected_id == id) node_flags |= ImGuiTreeNodeFlags_Selected;
				ImGui::Image(Resources::getFileFormatIcon("asset_font")); ImGui::SameLine();
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
				ImGui::TreeNodeEx(std::string(asset.second->getName()).c_str(), node_flags);

				// click node
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
					FontViewer::getInstance()->openFontViwer(pe::Assets::getAsset<pe::Font>(asset.second->getId())->getPath());
				}
				if (ImGui::IsItemClicked(0)) m_selected_id = id;
				if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
				if (id == m_selected_menu_id) renderRightMouseMenuFont(asset.second->getId());
			}

		}

		ImGui::TreePop();
	}
	else { // asset close
		if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenuAssets(path, id);
		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::getFileFormatIcon("assets_file"));
	}
}

void FileTree::renderRightMouseMenuAssets(const std::string& path, long long id) {
	if (ImGui::BeginPopupContextItem("right mouse menu")) {


		//ImGui::Image(Resources::getMenuIcon("open_in_explorer")); ImGui::SameLine();
		if (ImGui::Selectable("Open in TextEditor")) {
			std::string title = PyUtils::getInstance()->getOs().attr("path").attr("basename")(path).cast<std::string>();
			TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::C());
		}

		if (ImGui::Selectable("Reload")) {
			CLI::getInstance()->assetsFileUpdate();
		}

		ImGui::Image(Resources::getMenuIcon("open_in_explorer")); ImGui::SameLine();
		if (ImGui::Selectable("Open in Explorer")) {
			PyUtils::getInstance()->getOs().attr("system")(std::string("explorer \"").append(
				PyUtils::getInstance()->getOs().attr("path").attr("dirname")(path).cast<std::string>()
			).append("\""));
		}

		ImGui::EndPopup();
	}
}

void FileTree::renderRightMouseMenuTexture(int texture_id) {
	if (ImGui::BeginPopupContextItem("right mouse menu")) {
		bool modified = false;

		if (ImGui::MenuItem("Open in Image Viwer")) {
			ImageViewer::getInstance()->openImageViwer(pe::Assets::getAsset<pe::Texture>(texture_id)->getPath());
		}

		bool smooth = pe::Assets::getAsset<pe::Texture>(texture_id)->isSmooth();
		if (ImGui::MenuItem("Smooth", NULL, &smooth)) {
			pe::Assets::getAsset<pe::Texture>(texture_id)->setSmooth(smooth);
			modified = true;
			ImGui::CloseCurrentPopup();
		}
		bool repeated = pe::Assets::getAsset<pe::Texture>(texture_id)->isRepeated();
		if (ImGui::MenuItem("Repeated", NULL, &repeated)) {
			pe::Assets::getAsset<pe::Texture>(texture_id)->setRepeated(repeated);
			modified = true;
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::BeginMenu("See Path")) {
			ImGui::Text(pe::Assets::getAsset<pe::Texture>(texture_id)->getPath().c_str());
			ImGui::EndMenu();
		}

		if (modified) CLI::getInstance()->updateTexture(pe::Assets::getAsset<pe::Texture>(texture_id));

		ImGui::EndPopup();
	}
}

void FileTree::renderRightMouseMenuFont(int font_id) {
	if (ImGui::BeginPopupContextItem("right mouse menu")) {

		if (ImGui::MenuItem("Open in Font Viwer")) {
			FontViewer::getInstance()->openFontViwer(pe::Assets::getAsset<pe::Font>(font_id)->getPath());
		}

		if (ImGui::BeginMenu("See Path")) {
			ImGui::Text(pe::Assets::getAsset<pe::Font>(font_id)->getPath().c_str());
			ImGui::EndMenu();
		}

		ImGui::EndPopup();
	}
}
