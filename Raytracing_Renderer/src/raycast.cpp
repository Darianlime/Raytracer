#include "raycast.h"

Raycast::Raycast(Vec3 eye) : origin(eye) {}

Vec3 Raycast::GetOrigin() {
    return origin;
}

Vec3 Raycast::GetRayDir() {
    return raydir;
}

void Raycast::SetRayDir(Vec3 raydir)
{
    this->raydir = raydir;
}

void Raycast::SetRayDirAtPoint(Vec3 point)
{
    this->raydir = (point - origin) / Vec3::Mag(point - origin);
}

Vec3 Raycast::GetRay(float t)
{
    return origin + raydir * t;
}

// Check each object in the screen
// if no object found in front of eye return background color
// otherwise call ShadeRay()
Color Raycast::TraceRay(Vec3 point, Color background, vector<Object*> objects)
{
    SetRayDirAtPoint(point);
    //cout << "tracing: " << objects[0]->GetName() << endl;
    pair<Vec3, bool> o = objects[0]->CheckIntersection(Ray{origin, raydir});
    if (o.second) {
        return objects[0]->mat;
    }
    //o.first.ToString();
    //cout << o.second << endl;
    // Object closest; 
    // bool isIntersected = false;
    // for (Object obj : ) {
    //     // Create intersections for each object no in ray
    //     if (!SphereIntersecion())
    // }
    // if (isIntersected) {
    //     return ShadeRay(ColorObj);
    // }
    return background;
}