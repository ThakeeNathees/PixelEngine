#pragma once

// stl
#include <stdio.h>
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
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "PE-SFML.h"
#include "Logger.h"



#ifdef PE_PLATFORM_WINDOWS
	#define NOMINMAX
	#include <Windows.h>
#endif

