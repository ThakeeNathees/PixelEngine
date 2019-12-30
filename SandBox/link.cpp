#define PE_PROJECT SandBox
#include "register.h"

/* TODO: add relative path to linking
#pragma comment(lib, "lib/x64-release/Pixel-Engine.lib")
#pragma comment(lib, "lib/x64-release/sfml-audio.lib")
#pragma comment(lib, "lib/x64-release/sfml-graphics.lib")
#pragma comment(lib, "lib/x64-release/sfml-main.lib")
#pragma comment(lib, "lib/x64-release/sfml-network.lib")
#pragma comment(lib, "lib/x64-release/sfml-system.lib")
#pragma comment(lib, "lib/x64-release/sfml-window.lib")
*/


#ifdef _WIN32 // WINDOWS

#ifndef __MINGW32__ // Visual Studio

#ifdef _DEBUG
#pragma comment(lib, "Pixel-Engine.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#else
#pragma comment(lib, "Pixel-Engine.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-network.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#endif

#endif  // mingw
#endif  // windows


#ifdef __linux__ // LINUX
#endif