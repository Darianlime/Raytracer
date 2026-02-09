#include "color.h"

Color::Color() : r(0), g(0), b(0) {}

Color::Color(int red, int green, int blue, bool isNormalized) : r(red), g(green), b(blue) 
{
    if (isNormalized) {
        r *= 255;
        g *= 255;
        b *= 255;
    }
}

Color::Color(Vec3 rgb, bool isNormalized) : r(rgb.x), g(rgb.y), b(rgb.z) 
{
    if (isNormalized) {
        r *= 255;
        g *= 255;
        b *= 255;
    }
}

string Color::ToString() const {
    return to_string(r) + " " + to_string(g) + " " + to_string(b) + " ";
}