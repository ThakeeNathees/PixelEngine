#include "pch.h"
#include "FileTree.h"

#include "Popups.h"

FileTree* FileTree::s_instance = nullptr;

void FileTree::renderTreeRecursive(py::object& tree, bool next_item_open) {
	std::string path = tree.attr("path").cast<std::string>();
	long long id = m_math_util.attr("md5Hash")(path, "long").cast<long long>();
	std::string dir_name = m_py_os.attr("path").attr("basename")(path).cast<std::string>();

	float dir_icon_pos = ImGui::GetCursorPosX();
	if (next_item_open) ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode(path.c_str(), dir_name.c_str())) {
		// right click
		if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenu(path);
		// draw folder icon
		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::FileFormatIcons::DIR_OPEN);
		// loop for dirs
		for (int i = 0; i < tree.attr("dirs").attr("__len__")().cast<int>(); i++) {
			auto sub_tree = tree.attr("dirs").attr("__getitem__")(i);
			renderTreeRecursive(sub_tree);
		}
		// loop for files
		for (int i = 0; i < tree.attr("files").attr("__len__")().cast<int>(); i++) {
			std::string path = tree.attr("files").attr("__getitem__")(i).cast<std::string>();
			long long id = m_math_util.attr("md5Hash")(path, "long").cast<long long>();
			ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
			if (m_selected_id == id) node_flags |= ImGuiTreeNodeFlags_Selected;

			// draw file icon
			drawFileIcon(path);
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
			std::string title = m_py_os.attr("path").attr("basename")(path).cast<std::string>();
			ImGui::TreeNodeEx((void*)(intptr_t)(id), node_flags, title.c_str());

			// click node
			if (ImGui::IsItemClicked()) {
				m_selected_id = id;
				nodeClickedEvent(title, path, id);
			}
			if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
			if (id == m_selected_menu_id) renderRightMouseMenu(path);

		}
		ImGui::TreePop();
	}
	else {
		// right click
		if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenu(path);

		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::FileFormatIcons::DIR_CLOSED);
	}
}
/////////////////////////////////////////////////////////////

void FileTree::drawFileIcon(const std::string& file_name) {
	std::string format = getInstance()->getPyFileTree().attr("getFileFormat")(file_name).cast<std::string>();
	if (format == std::string("py")) { ImGui::Image(Resources::FileFormatIcons::FILE_PY); ImGui::SameLine(); return; }
	if (format == std::string("peproj")) { ImGui::Image(Resources::FileFormatIcons::FILE_PEPROJ); ImGui::SameLine(); return; }
	if (format == std::string("txt")) { ImGui::Image(Resources::FileFormatIcons::FILE_TEXT); ImGui::SameLine(); return; }
	if (format == std::string("ini")) { ImGui::Image(Resources::FileFormatIcons::FILE_TEXT); ImGui::SameLine(); return; }
	if (format == std::string("xml")) { ImGui::Image(Resources::FileFormatIcons::FILE_XML); ImGui::SameLine(); return; }
	if (format == std::string("pyc")) { ImGui::Image(Resources::FileFormatIcons::FILE_PYC); ImGui::SameLine(); return; }
	if (format == std::string("cpp")) { ImGui::Image(Resources::FileFormatIcons::FILE_CPP); ImGui::SameLine(); return; }
	if (format == std::string("h")) { ImGui::Image(Resources::FileFormatIcons::FILE_H); ImGui::SameLine(); return; }
	if (format == std::string("hpp")) { ImGui::Image(Resources::FileFormatIcons::FILE_HPP); ImGui::SameLine(); return; }
	if (format == std::string("png")) { ImGui::Image(Resources::FileFormatIcons::FILE_PNG); ImGui::SameLine(); return; }
	if (format == std::string("ttf")) { ImGui::Image(Resources::FileFormatIcons::FILE_TTF); ImGui::SameLine(); return; }
	// binary files
	if (format == std::string("exe")) { ImGui::Image(Resources::FileFormatIcons::FILE_BIN); ImGui::SameLine(); return; }
	if (format == std::string("lib")) { ImGui::Image(Resources::FileFormatIcons::FILE_BIN); ImGui::SameLine(); return; }
	if (format == std::string("dll")) { ImGui::Image(Resources::FileFormatIcons::FILE_DLL); ImGui::SameLine(); return; }
	if (format == std::string("obj")) { ImGui::Image(Resources::FileFormatIcons::FILE_OBJ); ImGui::SameLine(); return; }

	ImGui::Image(Resources::FileFormatIcons::_FILE_UNKNOWN); ImGui::SameLine();
}
/////////////////////////////////////////////////////////////

void FileTree::nodeClickedEvent(const std::string& title, const std::string& path, long long id) {

	if (title == std::string("LICENSE")) { TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::PlainText()); return; }

	std::string format = m_py_filetree.attr("getFileFormat")(path).cast<std::string>();
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

	if (format == std::string("ttf")) { FontViwers::openFontViwer(path, id); return; }
	if (format == std::string("png")) { return; }
	// binary files

}
/////////////////////////////////////////////////////////////

void FileTree::renderRightMouseMenu(const std::string& path) {
	if (ImGui::BeginPopupContextItem("right mouse menu")) {
		// for folder
		if (m_py_os.attr("path").attr("isdir")(path).cast<bool>()) {

			ImGui::Image(Resources::MenuIcons::NONE); ImGui::SameLine();
			if (ImGui::BeginMenu("New")) {
				ImGui::Image(Resources::FileFormatIcons::_FILE_UNKNOWN); ImGui::SameLine();
				if (ImGui::BeginMenu("File")) {
					ImGui::Text("Create a new file"); ImGui::Separator();
					static char file_name[1024];
					ImGui::Text("Name"); ImGui::SameLine();
					ImGui::InputText("", file_name, sizeof(file_name));
					if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
						m_py_os.attr("system")(std::string("copy NUL \"").append(
							m_py_os.attr("path").attr("join")(path, file_name).cast<std::string>()
						).append("\"")); reload();file_name[0] = 0;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}
				ImGui::Image(Resources::FileFormatIcons::DIR_CLOSED); ImGui::SameLine();
				if (ImGui::BeginMenu("Folder")) {
					ImGui::Text("Create a new folder"); ImGui::Separator();
					static char dir_name[1024];
					ImGui::Text("Name"); ImGui::SameLine();
					ImGui::InputText("", dir_name, sizeof(dir_name));
					if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
						m_py_os.attr("system")(std::string("mkdir \"").append(
							m_py_os.attr("path").attr("join")(path, dir_name).cast<std::string>()
						).append("\"")); reload(); dir_name[0] = 0;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			
			ImGui::Image(Resources::MenuIcons::RENAME); ImGui::SameLine();
			if (ImGui::BeginMenu("Rename")) {
				ImGui::Text("rename folder"); ImGui::Separator();
				static char new_name[1024];
				ImGui::Text("Name"); ImGui::SameLine();
				ImGui::InputText("", new_name, sizeof(new_name));
				if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
					m_py_os.attr("system")( std::string("rename \"").append(path).append("\" \"").append(new_name).append("\"") );
					reload(); new_name[0] = 0;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndMenu();
			}

			ImGui::Image(Resources::MenuIcons::_DELETE); ImGui::SameLine();
			if (ImGui::Selectable("Delete")) {
				Popups::PopupData data; data.path = path; data.is_path_dir = true;
				Popups::openPopup("Delete Conformation",data);
			}
			
			ImGui::Image(Resources::MenuIcons::OPEN_IN_EXPLORER); ImGui::SameLine();
			if (ImGui::Selectable("Open in explorer")) {
				m_py_os.attr("system")(std::string("explorer \"").append(path).append("\""));
			}
		}
		// for files
		else {

			ImGui::Image(Resources::MenuIcons::RENAME); ImGui::SameLine();
			if (ImGui::BeginMenu("Rename")) {
				ImGui::Text("rename folder"); ImGui::Separator();
				static char new_name[1024];
				ImGui::Text("Name"); ImGui::SameLine();
				ImGui::InputText("", new_name, sizeof(new_name));
				if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
					m_py_os.attr("system")(std::string("rename \"").append(path).append("\" \"").append(new_name).append("\""));
					reload(); new_name[0] = 0;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndMenu();
			}

			ImGui::Image(Resources::MenuIcons::_DELETE); ImGui::SameLine();
			if (ImGui::Selectable("Delete")) {
				Popups::PopupData data; data.path = path; data.is_path_dir = false;
				Popups::openPopup("Delete Conformation", data);
			}

			ImGui::Image(Resources::MenuIcons::OPEN_IN_EXPLORER); ImGui::SameLine();
			if (ImGui::Selectable("Open in explorer")) {
				m_py_os.attr("system")(std::string("explorer \"").append(
					m_py_os.attr("path").attr("dirname")(path).cast<std::string>()
				).append("\""));
			}
		}
		ImGui::EndPopup();

	}
}
/////////////////////////////////////////////////////////////