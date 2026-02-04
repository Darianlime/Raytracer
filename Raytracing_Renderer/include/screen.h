#include <vector>

#include "vector.h"
#include "camera.h"
#include "color.h"

#ifndef SCREEN_H
#define SCREEN_H

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
        void CalcWindowCorners(Camera cam, float viewDist);

}; 

#endif