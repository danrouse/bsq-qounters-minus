#include "format.hpp"

std::string FormatNumber(float number, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << number;
    return stream.str();
}

std::string FormatColorToHex(float r, float g, float b) {
    std::stringstream stream;
    stream << std::hex << ((int)(r * 255) << 16 | (int)(g * 255) << 8 | (int)(b * 255));
    return stream.str();
}
