#include "color.h"

Color::Color() : r(0), g(0), b(0) {}

Color::Color(float red, float green, float blue, bool isNormalized)
{
    if (isNormalized) {
        r = red * 255;
        g = green * 255;
        b = blue * 255;
    } else {
        r = red;
        g = green;
        b = blue;
    }
}

Color::Color(Vec3 rgb, bool isNormalized) : r(rgb.x), g(rgb.y), b(rgb.z) 
{
    if (isNormalized) {
        r = rgb.x * 255;
        g = rgb.y * 255;
        b = rgb.z * 255;
    } else {
        r = rgb.x;
        g = rgb.y;
        b = rgb.z;
    }
}

string Color::ToString() const {
    return to_string(r) + " " + to_string(g) + " " + to_string(b) + " ";
}