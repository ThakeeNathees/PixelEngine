#include "pch.h"

#include "StartWindow.h"
#include "FileTree.h"
#include "TextEditors.h"
#include "HexEditors.h"
#include "FontViwers.h"

#include "PyInterpriter.h"
#include "Explorer.h"

StartWindow* StartWindow::s_instance = nullptr;
ExplorerPopup* ExplorerPopup::s_instance = nullptr;
PyInterpriter* PyInterpriter::s_instance = nullptr;

// TODO: remove text editors
std::map<long long, TextEditors::TextEditorData*> TextEditors::s_text_editors;
std::map<long long, HexEditors::HexEditorData*> HexEditors::s_hex_editors;
std::map<long long, FontViwers::FontData*> FontViwers::s_fonts;
