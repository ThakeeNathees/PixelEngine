#pragma once

// stl
#include <stdio.h>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <functional>
#include <algorithm>
#include <utility>

// data structures
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// other
#include <glm/glm.hpp>
using namespace glm;
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Logger.h"


#ifdef PE_PLATFORM_WINDOWS
	#define NOMINMAX
	#include <Windows.h>
#endif

