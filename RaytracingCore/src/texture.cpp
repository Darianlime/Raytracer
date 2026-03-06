#include "texture.h"

Texture::Texture() : width(0), height(0), pixels() {}

Texture::Texture(int width, int height, std::vector<Color>& pixels) : width(width), height(height), pixels(pixels) {}

Color Texture::GetPixel(float u, float v) {
    if (u > 1 || v > 1) {
        double interI;
        double interJ;
        int i = round(modf(u, &interI) * (width-1));
        int j = round(modf(v, &interJ) * (height-1));
        Color color = pixels[j * width + i];
        color.Normlize();
        return color;
    }
    Vec2 current(u * (width-1), v * (height-1)); 
    int i = (int)current.x;
    int j = (int)current.y;
    float alpha = current.x - i;
    float beta = current.y - j;
    Vec3 weightTL = pixels[j * width + i].GetVec() * ((1 - alpha) * (1 - beta));
    Vec3 weightTR = pixels[j * width + (i+1)].GetVec() * (alpha * (1-beta));
    Vec3 weightBL = pixels[(j+1) * width + i].GetVec() * ((1-alpha) * beta);
    Vec3 weightBR = pixels[(j+1) * width + (i+1)].GetVec() * (alpha * beta);    
    Color color = Color(weightTL + weightTR + weightBL + weightBR);
    color.Normlize();
    return color;
    // Vec2 current(u * width, v * height); 
    // Color color = pixels[(int)(v * height) * width + (int)(u * width)];
    // color.Normlize();
    // return color;
}