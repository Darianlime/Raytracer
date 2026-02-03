#include "vector.h"
#include "camera.h"

#ifndef SCREEN_H
#define SCREEN_H

class Screen {
    private:
        // screen resolution
        int width;
        int height;

        // 4 corners of viewing window
        Vec3 upper_left;
        Vec3 upper_right;
        Vec3 lower_left;
        Vec3 lower_right;
    public:
        Screen();
        Screen(int width, int height);
        void CalcWindowCorners(Camera cam, float viewDist);

}; 

#endif