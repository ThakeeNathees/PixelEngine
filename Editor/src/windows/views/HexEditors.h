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

	static void openHexEditor(const std::string& title, const std::string& path, long long id) {
		if (s_hex_editors.find(id) == s_hex_editors.end())
			s_hex_editors[id] = new HexEditorData(title, path);
		else s_hex_editors[id]->p_open = true;
	}

	static void renderEditors() {
		for (auto pair: s_hex_editors) {
			if (pair.second->p_open && !pair.second->error_read) {
				pair.second->memedit.DrawWindow(pair.second->title.c_str(), (void*) & (pair.second->buffer[0]), pair.second->buffer.size(), &(pair.second->p_open));
			}
		}
	}

private:
	HexEditors() {}
	static std::map<long long, HexEditorData*> s_hex_editors;
};
