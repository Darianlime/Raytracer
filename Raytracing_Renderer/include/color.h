#ifndef COLOR_H
#define COLOR_H

#include "vector.h"

#include <algorithm>
#include <cstdint>
#include <string>

using namespace std;

struct Color {
	int r;
	int g;
	int b;

	Color();
	Color(float red, float green, float blue, bool isNormalized);
	Color(Vec3 rgb, bool isNormalized);

    void ClampValues(bool isNormalized);

    Vec3 GetVec() const { return Vec3(r, g, b); }
	string ToString() const;
	int CheckArgs();
};

#endif