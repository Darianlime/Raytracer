#ifndef COLOR_H
#define COLOR_H

#include "vector.h"

#include <cstdint>
#include <string>

using namespace std;

struct Color {
	int r;
	int g;
	int b;

	Color();
	Color(int red, int green, int blue, bool isNormalized);
	Color(Vec3 rgb, bool isNormalized);

	string ToString() const;
};

#endif