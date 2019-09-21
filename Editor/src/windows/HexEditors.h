#pragma once

class HexEditors
{
public:
	struct HexEditorData {
		HexEditorData(const std::string& _title="__default_hex_editor", const std::string& _path="") {
			title = _title;
			error_read = CLI::readBinaryFile(buffer, _path); // TODO: handle error
			memedit.Cols = 16;
		}
		MemoryEditor memedit;
		std::string title;
		bool error_read = true;
		bool p_open = true;
		std::vector<unsigned char> buffer;
	};

	static void addHexEditor(const std::string& title, const std::string& path) {
		s_hex_editors.push_back(new HexEditorData(title, path));
	}

	static void renderEditors() {
		for (auto hex : s_hex_editors) {
			if (hex->p_open && !hex->error_read) {
				hex->memedit.DrawWindow(hex->title.c_str(), (void*) & (hex->buffer[0]), hex->buffer.size(), &(hex->p_open));
			}
		}
	}

private:
	HexEditors() {}
	static std::vector<HexEditorData*> s_hex_editors;
};
