#include "format.hpp"

std::string FormatNumber(float number, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << number;
    return stream.str();
}

#include "logger.hpp"
std::string FormatColorToHex(UnityEngine::Color color) {
    std::stringstream stream;
    stream << std::hex << std::setw(6) << std::setfill('0') << ((int)(color.r * 255) << 16 | (int)(color.g * 255) << 8 | (int)(color.b * 255));
    return "#" + stream.str();
}
