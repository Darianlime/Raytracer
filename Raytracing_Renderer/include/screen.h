#ifndef SCREEN_H
#define SCREEN_H

#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>

#include "vector.h"
#include "camera.h"
#include "color.h"

class Screen {
    private:
        // screen resolution
        int width;
        int height;

        vector<vector<Color>> pixels;

        // 4 corners of viewing window
        Vec3 upper_left;
        Vec3 upper_right;
        Vec3 lower_left;
        Vec3 lower_right;
    public:
        Color bkgcolor;

        Screen();
        Screen(int width, int height, Color bkgcolor);
        void CalcWindowCorners(Camera cam);
        int GetWidth() const { return width; }
        int GetHeight() const { return height; }

        Vec3 GetDV() const { return (lower_left - upper_left) / (height - 1); }
        Vec3 GetDH() const { return (upper_right - upper_left) / (width - 1); }

        Vec3 GetWindowLocation(int width, int height) const { return upper_left + GetDH() * width + GetDV() * height; }

        vector<vector<Color>>& GetPixels() { return pixels; }

}; 

#endif