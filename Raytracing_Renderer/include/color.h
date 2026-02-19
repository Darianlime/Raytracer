#ifndef COLOR_H
#define COLOR_H

#include "vector.h"

#include <algorithm>
#include <cstdint>
#include <string>

using namespace std;

struct Color {
	float r;
	float g;
	float b;
	bool isNormalized;

	Color();
	Color(float red, float green, float blue, bool isNormalized);
	Color(Vec3 rgb, bool isNormalized);

    void ClampValues(bool isNormalized);

	// float R() { if (isNormalized) { return (int)round(r); } return r; }
	// float G() { if (isNormalized) { return (int)round(g); } return g; }
	// float B() { if (isNormalized) { return (int)round(b); } return b; }

    Vec3 GetVec() { return Vec3(r, g, b); }
	string ToString() const;
	int CheckArgs();
};

#endif