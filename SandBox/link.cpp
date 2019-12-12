#define PE_PROJECT SandBox
#include "register.h"

#ifdef _DEBUG
#pragma comment(lib, "lib/x64-debug/Pixel-Engine.lib")
#pragma comment(lib, "lib/x64-debug/sfml-audio-d.lib")
#pragma comment(lib, "lib/x64-debug/sfml-graphics-d.lib")
#pragma comment(lib, "lib/x64-debug/sfml-main-d.lib")
#pragma comment(lib, "lib/x64-debug/sfml-network-d.lib")
#pragma comment(lib, "lib/x64-debug/sfml-system-d.lib")
#pragma comment(lib, "lib/x64-debug/sfml-window-d.lib")
#else
#pragma comment(lib, "lib/x64-release/Pixel-Engine.lib")
#pragma comment(lib, "lib/x64-release/sfml-audio.lib")
#pragma comment(lib, "lib/x64-release/sfml-graphics.lib")
#pragma comment(lib, "lib/x64-release/sfml-main.lib")
#pragma comment(lib, "lib/x64-release/sfml-network.lib")
#pragma comment(lib, "lib/x64-release/sfml-system.lib")
#pragma comment(lib, "lib/x64-release/sfml-window.lib")
#endif