#pragma once

#include <sstream>
#include <iomanip>
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "UnityEngine/Color.hpp"

std::string FormatNumber(float number, int precision);
std::string FormatColorToHex(UnityEngine::Color color);
