#include "pch.h"
#include "FileTree.h"

FileTree* FileTree::s_instance = nullptr;

void FileTree::renderTreeRecursive(py::object& tree, bool next_item_open) {
	std::string path = tree.attr("path").cast<std::string>();
	long long id = PyUtils::getInstance()->getMathUtil().attr("md5Hash")(path, "long").cast<long long>();
	std::string dir_name = PyUtils::getInstance()->getOs().attr("path").attr("basename")(path).cast<std::string>();

	float dir_icon_pos = ImGui::GetCursorPosX();
	if (next_item_open) ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode(path.c_str(), dir_name.c_str())) {
		// right click
		if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenu(path);

		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::getFileFormatIcon("dir_open"));
		// loop for dirs
		for (int i = 0; i < tree.attr("dirs").attr("__len__")().cast<int>(); i++) {
			auto sub_tree = tree.attr("dirs").attr("__getitem__")(i);
			renderTreeRecursive(sub_tree);
		}
		// loop for files
		for (int i = 0; i < tree.attr("files").attr("__len__")().cast<int>(); i++) {
			std::string path = tree.attr("files").attr("__getitem__")(i).cast<std::string>();

			// pe special files like assets.xml, *.obj.xml, *.scn.xml, *.peproj
			if (tree.attr("isAssetFile")(i).cast<bool>()) {
				renderAssetsTree(path);
			}
			else if (tree.attr("isObjectFile")(i).cast<bool>()) {
				renderObjectTree(path);
			}
			else if (tree.attr("isSceneFile")(i).cast<bool>()) {
				renderSceneTree(path);
			}
			else {
				long long id = PyUtils::getInstance()->getMathUtil().attr("md5Hash")(path, "long").cast<long long>();
				ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
				if (m_selected_id == id) node_flags |= ImGuiTreeNodeFlags_Selected;


				// draw file icon
				Resources::drawFileIcon(path); ImGui::SameLine();
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
				std::string title = PyUtils::getInstance()->getOs().attr("path").attr("basename")(path).cast<std::string>();
				ImGui::TreeNodeEx((void*)(intptr_t)(id), node_flags, title.c_str());

				// click node
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
					m_selected_id = id;
					nodeClickedEvent(title, path, id);
				}
				if (ImGui::IsItemClicked(0)) m_selected_id = id;
				if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
				if (id == m_selected_menu_id) renderRightMouseMenu(path);
			}
		}
		ImGui::TreePop();
	}
	else { // dir closed
		// right click
		if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenu(path);

		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::getFileFormatIcon("dir_close"));
	}
}
/////////////////////////////////////////////////////////////


void FileTree::nodeClickedEvent(const std::string& title, const std::string& _path, long long id) {
	auto path = PyUtils::getInstance()->getOs().attr("path").attr("relpath")(_path).cast<std::string>();

	if (title == std::string("LICENSE")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::PlainText()); return; }

	std::string format = PyUtils::getInstance()->getFileUtil().attr("getFileFormat")(path).cast<std::string>();

	if (format == std::string("py")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::Python()); return; }
	if (format == std::string("peproj")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::C()); return; }
	if (format == std::string("txt")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::PlainText()); return; }
	if (format == std::string("ini")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::PlainText()); return; }
	if (format == std::string("init")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::PlainText()); return; }
	if (format == std::string("xml")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::C()); return; }
	if (format == std::string("cpp")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::CPlusPlus());  return; }
	if (format == std::string("h")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::CPlusPlus()); return; }
	if (format == std::string("hpp")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::CPlusPlus()); return; }

	if (format == std::string("pyc")) { HexEditors::openHexEditor(title, path, id);  return; }
	if (format == std::string("exe")) { HexEditors::openHexEditor(title, path, id);  return; }
	if (format == std::string("lib")) { HexEditors::openHexEditor(title, path, id);  return; }
	if (format == std::string("dll")) { HexEditors::openHexEditor(title, path, id);  return; }
	if (format == std::string("obj")) { HexEditors::openHexEditor(title, path, id);  return; }
	if (format == std::string("inl")) { HexEditors::openHexEditor(title, path, id);  return; }

	if (format == std::string("ttf")) { FontViwer::getInstance()->openFontViwer(path); return; }
	if (format == std::string("png")) {  ImageViwer::getInstance()->openImageViwer(path ); return; }
	if (format == std::string("jpg")) {  ImageViwer::getInstance()->openImageViwer(path ); return; }
	if (format == std::string("jpeg")) { ImageViwer::getInstance()->openImageViwer(path); return; }
	// binary files

}
/////////////////////////////////////////////////////////////

void FileTree::renderRightMouseMenu(const std::string& path) {
	if (ImGui::BeginPopupContextItem("right mouse menu")) {
		// for folder
		if (PyUtils::getInstance()->getOs().attr("path").attr("isdir")(path).cast<bool>()) {

			ImGui::Image(Resources::getMenuIcon("none")); ImGui::SameLine();
			if (ImGui::BeginMenu("New")) {
				//ImGui::Image(Resources::FileFormatIcons::_FILE_UNKNOWN); ImGui::SameLine();
				ImGui::Image(Resources::getFileFormatIcon("file_unknown")); ImGui::SameLine();
				if (ImGui::BeginMenu("File")) {
					ImGui::Text("Create a new file"); ImGui::Separator();
					static char file_name[1024];
					ImGui::Text("Name"); ImGui::SameLine();
					ImGui::InputText("", file_name, sizeof(file_name));
					if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
						PyUtils::getInstance()->getOs().attr("system")(std::string("copy NUL \"").append(
							PyUtils::getInstance()->getOs().attr("path").attr("join")(path, file_name).cast<std::string>()
						).append("\"")); reload();file_name[0] = 0;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}
				ImGui::Image(Resources::getFileFormatIcon("dir_close")); ImGui::SameLine();
				if (ImGui::BeginMenu("Folder")) {
					ImGui::Text("Create a new folder"); ImGui::Separator();
					static char dir_name[1024];
					ImGui::Text("Name"); ImGui::SameLine();
					ImGui::InputText("", dir_name, sizeof(dir_name));
					if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
						PyUtils::getInstance()->getOs().attr("system")(std::string("mkdir \"").append(
							PyUtils::getInstance()->getOs().attr("path").attr("join")(path, dir_name).cast<std::string>()
						).append("\"")); reload(); dir_name[0] = 0;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			
			ImGui::Image(Resources::getMenuIcon("rename")); ImGui::SameLine();
			if (ImGui::BeginMenu("Rename")) {
				ImGui::Text("rename folder"); ImGui::Separator();
				static char new_name[1024];
				ImGui::Text("Name"); ImGui::SameLine();
				ImGui::InputText("", new_name, sizeof(new_name));
				if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
					PyUtils::getInstance()->getOs().attr("system")( std::string("rename \"").append(path).append("\" \"").append(new_name).append("\"") );
					reload(); new_name[0] = 0;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndMenu();
			}

			ImGui::Image(Resources::getMenuIcon("delete")); ImGui::SameLine();
			if (ImGui::Selectable("Delete")) {
				m_delete_path = path;
				m_is_deletepathdir = true;
				m_open_popup = true;
			}
			
			ImGui::Image(Resources::getMenuIcon("open_in_explorer")); ImGui::SameLine();
			if (ImGui::Selectable("Open in explorer")) {
				PyUtils::getInstance()->getOs().attr("system")(std::string("explorer \"").append(path).append("\""));
			}
		}
		// for files
		else {

			ImGui::Image(Resources::getMenuIcon("rename")); ImGui::SameLine();
			if (ImGui::BeginMenu("Rename")) {
				ImGui::Text("rename folder"); ImGui::Separator();
				static char new_name[1024];
				ImGui::Text("Name"); ImGui::SameLine();
				ImGui::InputText("", new_name, sizeof(new_name));
				if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
					PyUtils::getInstance()->getOs().attr("system")(std::string("rename \"").append(path).append("\" \"").append(new_name).append("\""));
					reload(); new_name[0] = 0;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndMenu();
			}

			ImGui::Image(Resources::getMenuIcon("delete")); ImGui::SameLine();
			if (ImGui::Selectable("Delete")) {
				m_delete_path = path;
				m_is_deletepathdir = false;
				m_open_popup = true;
			}

			ImGui::Image(Resources::getMenuIcon("open_in_explorer")); ImGui::SameLine();
			if (ImGui::Selectable("Open in explorer")) {
				PyUtils::getInstance()->getOs().attr("system")(std::string("explorer \"").append(
					PyUtils::getInstance()->getOs().attr("path").attr("dirname")(path).cast<std::string>()
				).append("\""));
			}
		}
		ImGui::EndPopup();

	}
}

/////////////////////////////////////////////////////////////

void FileTree::renderPopup() {

	if (m_open_popup) ImGui::OpenPopup("Delete Conformation");

	if (ImGui::BeginPopupModal("Delete Conformation", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		auto py_os = py::module::import("os");
		// folder
		if (m_is_deletepathdir) {
			ImGui::Image(Resources::getOtherIcon("warning")); ImGui::SameLine();
			ImGui::Text("All the files and It's contents \nwill be deleted permenently.\nThis operation cannot be undone!\n\n");
			ImGui::Separator();
			if (ImGui::Button("OK", ImVec2(120, 0))) {
				py_os.attr("system")(std::string("RD /S /Q \"").append(m_delete_path).append("\"")); FileTree::getInstance()->reload();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		}
		else {
			ImGui::Image(Resources::getOtherIcon("warning")); ImGui::SameLine();
			ImGui::Text("The file will be deleted permenently.\nThis operation cannot be undone!\n\n");
			ImGui::Separator();
			if (ImGui::Button("OK", ImVec2(120, 0))) {
				py_os.attr("system")(std::string("del \"").append(m_delete_path).append("\"")); FileTree::getInstance()->reload();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		}

		ImGui::SetItemDefaultFocus();
		ImGui::EndPopup();

		if (!ImGui::IsPopupOpen("Delete Conformation")) m_open_popup = false;
	}
}