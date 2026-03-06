#include "color.h"

using std::string;
using std::to_string;
using std::clamp;
using std::cerr;
using std::endl;

Color::Color() : r(0), g(0), b(0), isNormalized(false) {}

Color::Color(float red, float green, float blue) : r(red), g(green), b(blue), isNormalized(false) {}

Color::Color(Vec3 rgb) : r(rgb.x), g(rgb.y), b(rgb.z), isNormalized(false) {}

Color::Color(float red, float green, float blue, bool isNormalized) : isNormalized(isNormalized)
{
    if (isNormalized) {
        r = clamp(red * 255, 0.0f, 255.0f);
        g = clamp(green * 255, 0.0f, 255.0f);
        b = clamp(blue * 255, 0.0f, 255.0f);
    } else {
        r = red;
        g = green;
        b = blue;
    }
    ClampValues(isNormalized);
}

Color::Color(Vec3 rgb, bool isNormalized) : isNormalized(isNormalized)
{
    if (isNormalized) {
        r = clamp(rgb.x * 255, 0.0f, 255.0f);
        g = clamp(rgb.y * 255, 0.0f, 255.0f);
        b = clamp(rgb.z * 255, 0.0f, 255.0f);
    } else {
        r = rgb.x;
        g = rgb.y;
        b = rgb.z;
    }
    ClampValues(isNormalized);

}

void Color::ClampValues(bool isNormalized) {
    if (isNormalized) {
        r = (int)round(r);
        g = (int)round(g);
        b = (int)round(b);
        r = clamp(r, 0.0f, 255.0f);
        g = clamp(g, 0.0f, 255.0f);
        b = clamp(b, 0.0f, 255.0f);
    } else {
        r = clamp(r, 0.0f, 1.0f);
        g = clamp(g, 0.0f, 1.0f);
        b = clamp(b, 0.0f, 1.0f);
    }
}

void Color::Normlize()
{
    r = r/255;
    g = g/255;
    b = b/255;
}

string Color::ToString() const {
    if (isNormalized) {
        return to_string(static_cast<int>(r)) + " " + to_string(static_cast<int>(g)) + " " + to_string(static_cast<int>(b)) + " ";
    }
    return to_string(r) + " " + to_string(g) + " " + to_string(b) + " ";
}

int Color::CheckArgs()
{
    if (r > 255) { cerr << "red rgb is greater than 255" << endl; return -1; }
    if (g > 255) { cerr << "green rgb is greater than 255" << endl; return -1; }
    if (b > 255) { cerr << "blue rgb is greater than 255" << endl; return -1; }
    if (r < 0) { cerr << "red rgb is less than 0" << endl; return -1; }
    if (g < 0) { cerr << "green rgb is less than 0" << endl; return -1; }
    if (b < 0) { cerr << "blue rgb is less than 0" << endl; return -1; }
    return 0;
}
