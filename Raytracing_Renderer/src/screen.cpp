#include "screen.h"

Screen::Screen() {}

Screen::Screen(int width, int height) : width(width), height(height) {}

void Screen::CalcWindowCorners(Camera cam, float viewDist) {
    Vec3 p = cam.GetEye() + cam.GetViewDir() * viewDist;
    upper_left = p - cam.GetU() * (width/2) + cam.GetV() * (height/2);
    upper_right = p + cam.GetU() * (width/2) + cam.GetV() * (height/2);
    lower_left = p - cam.GetU() * (width/2) - cam.GetV() * (height/2);
    lower_right = p + cam.GetU() * (width/2) - cam.GetV() * (height/2);
    
    upper_left.ToString();
    upper_right.ToString();
    lower_left.ToString();
    lower_right.ToString();
}