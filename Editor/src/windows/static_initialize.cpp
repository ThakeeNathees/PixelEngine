#include "pch.h"
#include "FileTree.h"
#include "TextEditors.h"
#include "HexEditors.h"
#include "FontViwers.h"


FileTree* FileTree::s_instance = nullptr;
// TODO: remove text editors
std::map<long long, TextEditors::TextEditorData*> TextEditors::s_text_editors;
std::vector<HexEditors::HexEditorData*> HexEditors::s_hex_editors;
std::vector<FontViwers::FontData*> FontViwers::s_fonts;