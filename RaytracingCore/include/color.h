#ifndef COLOR_H
#define COLOR_H

#include "vector.h"

#include <algorithm>
#include <cstdint>
#include <string>

struct Color {
	float r;
	float g;
	float b;
	float refractionIndex;
	bool isNormalized;

	Color();
    Color(float red, float green, float blue);
    Color(Vec3 rgb);
    Color(float red, float green, float blue, bool isNormalized);
    Color(Vec3 rgb, bool isNormalized);

    void ClampValues(bool isNormalized);
	void Normlize();

    Vec3 GetVec() const { return Vec3(r, g, b); }
	std::string ToString() const;
	int CheckArgs();
};

#endif