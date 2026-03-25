#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include "color.h"

struct Texture {
    int width;
    int height;
    std::vector<Color> pixels;

	Texture();
    Texture(int width, int height, std::vector<Color> &pixels);
    Color GetPixel(float u, float v) const;
};

#endif