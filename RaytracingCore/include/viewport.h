#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <vector>

#include "vector.h"
#include "camera.h"
#include "color.h"

namespace Raytracer {
class Viewport {
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

        Viewport();
        Viewport(int width, int height, Color bkgcolor);
        void CalcWindowCorners(Camera cam);
        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        void SetWidth(int width) { width = width; }
        void SetHeight(int height) { height = height; }
        void SetWidthHeight(int width, int height) { width = width; height = height; }
        void SetHeight(int height) { height = height; }

        Vec3 GetDV() const { return (lower_left - upper_left) / (height - 1); }
        Vec3 GetDH() const { return (upper_right - upper_left) / (width - 1); }

        Vec3 GetWindowLocation(int width, int height) const { return upper_left + GetDH() * width + GetDV() * height; }

        vector<vector<Color>>& GetPixels() { return pixels; }

}; 
}
#endif