#include "viewport.h"

using std::vector;

namespace Raytracer {
    Viewport::Viewport() : width(1), height(1), bkgcolor(Color(0.0f,0.0f,0.0f, true)), pixels(width, vector<Color>(height)) {}

    Viewport::Viewport(int width, int height, Color bkgcolor) : width(width), height(height), bkgcolor(bkgcolor), pixels(width, vector<Color>(height)) {}

    void Viewport::CalcWindowCorners(Camera cam) {

        float vfov = cam.GetVFov() * M_PI / 180;
        float viewDist = 1;
        
        float viewportHeight = 2 * tan(vfov / 2);
        float viewportWidth = viewportHeight * ((float)width / height);

        Vec3 p = cam.GetEye() + cam.GetViewDir().Normalize() * viewDist;
        upper_left = p - cam.GetU() * (viewportWidth/2) + cam.GetV() * (viewportHeight/2);
        upper_right = p + cam.GetU() * (viewportWidth/2) + cam.GetV() * (viewportHeight/2);
        lower_left = p - cam.GetU() * (viewportWidth/2) - cam.GetV() * (viewportHeight/2);
        lower_right = p + cam.GetU() * (viewportWidth/2) - cam.GetV() * (viewportHeight/2);
        
        p.ToString();
        upper_left.ToString();
        upper_right.ToString();
        lower_left.ToString();
        lower_right.ToString();
    }
}