#include "pch.h"
#include "globals.h"

std::shared_ptr<Globals> Globals::m_globals = std::shared_ptr<Globals>();

std::string Globals::FileTree::selected_file_path = "";
bool Globals::FileTree::is_clicked_now = false;