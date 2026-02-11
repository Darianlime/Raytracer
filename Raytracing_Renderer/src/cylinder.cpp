#include "objects/cylinder.h"

Cylinder::Cylinder(Vec3 pos, Vec3 direction, float radius, float length, Color mat) 
    : Object(pos, mat, "cylinder"), radius(radius), direction(direction), length(length) {}

pair<Vec3, bool> Cylinder::CheckIntersection(Ray ray) {
    Vec3 f = ray.origin - pos;
    float A = Vec3::Dot(ray.raydir, ray.raydir) - pow(Vec3::Dot(ray.raydir, direction),2);
    float B = 2 * (Vec3::Dot(ray.raydir, f) - Vec3::Dot(ray.raydir, direction) * Vec3::Dot(f, direction));
    float C = Vec3::Dot(f, f) - pow(Vec3::Dot(f, direction),2) - pow(radius,2);
    
    float t = GetHitDistance(A, B, C);
    if (t < 0) {
        return pair<Vec3, bool>(Vec3(0,0,0), false);
    }

    Vec3 intersectedPoint = ray.GetRay(t);
    Vec3 w = intersectedPoint - pos;
    float alpha = Vec3::Dot(w, direction) / Vec3::Dot(direction, direction);
    if (0 <= alpha && alpha <= length) {
        return pair<Vec3, bool>(intersectedPoint, true);
    }
    return pair<Vec3, bool>(Vec3(0,0,0), false);
}