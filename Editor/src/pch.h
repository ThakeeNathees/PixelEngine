#pragma once

#include <imgui.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <imgui-SFML.h>
#include <imgui_memory_editor.h>
#include <TextEditor.h>
#include <Pixel-Engine.h>


#include <stdio.h>
#include <memory>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <assert.h>

#include <algorithm>
#include <math.h>
#include <string>
#include <vector>


#include <pybind11/stl.h>
#include "pybind11/embed.h"
namespace py = pybind11;

#define snprintf _snprintf_s



/* logo color bottom left to top right

sf::Color(20,105,170)
sf::Color(20,124,185)
sf::Color(20,143,183)

sf::Color(39,130,199)
sf::Color(29,155,217)
sf::Color(15,168,221)

sf::Color(15,185,237)
sf::Color(51,194,235)
sf::Color(64,196,225)
*/