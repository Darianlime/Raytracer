#include "raycast.h"

Raycast::Raycast(Vec3 eye) : pos(eye) {}

void Raycast::SetRayDir(Vec3 point)
{
    raydir = (point - pos) / Vec3::Mag(point - pos);
}

Vec3 Raycast::GetRay(float t)
{

    return pos + raydir * t;
}

// Check each object in the screen
// if no object found in front of eye return background color
// otherwise call ShadeRay()
Color Raycast::TraceRay()
{

    return Color();
}