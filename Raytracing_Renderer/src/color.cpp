#include "color.h"

Color::Color() : r(0), g(0), b(0) {}

Color::Color(int red, int green, int blue)
    : r(red), g(green), b(blue) {}

string Color::ToString() const {
    return to_string(r) + " " + to_string(g) + " " + to_string(b) + " ";
}