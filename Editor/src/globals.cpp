#include "pch.h"
#include "globals.h"

// global data
//pe::Assets Globals::s_assets;
std::string Globals::s_working_dir;

// other window data
std::string Globals::FileTree::selected_file_path = "";
bool Globals::FileTree::is_clicked_now = false;
bool Globals::TextEditor::is_currently_rendering_window_focus = false;