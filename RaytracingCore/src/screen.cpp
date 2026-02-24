#include "screen.h"

namespace Raytracer {
    Screen::Screen() {}

    Screen::Screen(int width, int height, Color bkgcolor) : width(width), height(height), bkgcolor(bkgcolor), pixels(width, vector<Color>(height)) {}

    void Screen::CalcWindowCorners(Camera cam) {

        float vfov = cam.GetVFov();
        float viewDist = (height/2) / tan((vfov/2) * (M_PI / 180));

        Vec3 p = cam.GetEye() + cam.GetViewDir() * viewDist;
        upper_left = p - cam.GetU() * (width/2) + cam.GetV() * (height/2);
        upper_right = p + cam.GetU() * (width/2) + cam.GetV() * (height/2);
        lower_left = p - cam.GetU() * (width/2) - cam.GetV() * (height/2);
        lower_right = p + cam.GetU() * (width/2) - cam.GetV() * (height/2);
        
        p.ToString();
        upper_left.ToString();
        upper_right.ToString();
        lower_left.ToString();
        lower_right.ToString();
    }
}