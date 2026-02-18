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
    ClampValues(isNormalized);
}

Color::Color(Vec3 rgb, bool isNormalized)
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
    ClampValues(isNormalized);

}

void Color::ClampValues(bool isNormalized) {
    if (isNormalized) {
        r = clamp(r, 0, 255);
        g = clamp(g, 0, 255);
        b = clamp(b, 0, 255);
    } else {
        r = clamp(r, 0, 1);
        g = clamp(g, 0, 1);
        b = clamp(b, 0, 1);
    }
}

string Color::ToString() const {
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
