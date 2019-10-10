#include "pch.h"

#include "StartWindow.h"
#include "FileTree.h"
#include "windows/views/TextEditors.h"
#include "windows/views/HexEditors.h"
#include "windows/views/FontViwers.h"
#include "windows/views/ImageViwers.h"

#include "PyInterpriter.h"
#include "ExplorerPopup.h"

StartWindow* StartWindow::s_instance = nullptr;
ExplorerPopup* ExplorerPopup::s_instance = nullptr;
PyInterpriter* PyInterpriter::s_instance = nullptr;

// TODO: remove text editors
std::map<long long, TextEditors::TextEditorData*> TextEditors::s_text_editors;
std::map<long long, HexEditors::HexEditorData*> HexEditors::s_hex_editors;


FontViwer* FontViwer::s_instance;
ImageViwer* ImageViwer::s_instance;
float TextEditors::s_font_scale = 100;
std::string TextEditors::s_font = ""; // "" means ImGui default font

