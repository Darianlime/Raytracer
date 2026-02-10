#include "objects/cylinder.h"

Cylinder::Cylinder(Vec3 pos, Vec3 direction, float radius, float length, Color mat) 
    : Object(pos, mat, "cylinder"), radius(radius), direction(direction), length(length) {}

pair<Vec3, bool> Cylinder::CheckIntersection(Ray ray) {
    Vec3 f = ray.origin - pos;
    float A = Vec3::Dot(ray.raydir, ray.raydir) - pow(Vec3::Dot(ray.raydir, direction),2);
    float B = 2 * (Vec3::Dot(ray.raydir, f) - Vec3::Dot(ray.raydir, direction) * Vec3::Dot(f, direction));
    float C = Vec3::Dot(f, f) - pow(Vec3::Dot(f, direction),2) - pow(radius,2);
    float discriminant = pow(B, 2) - 4 * A * C;
    if (discriminant < 0) {
        return pair<Vec3, bool>(Vec3(0,0,0), false);
    }

    float t = (-B - sqrt(discriminant)) / (2 * A); 
    float t2 = (-B + sqrt(discriminant)) / (2 * A); 
    if (t < 0 || t2 < 0) {
        return pair<Vec3, bool>(Vec3(0,0,0), false);
    }
    if (t2 < t) {
        t = t2;
    }
    Vec3 intersectedPoint = ray.GetRay(t);
    Vec3 w = intersectedPoint - pos;
    float alpha = Vec3::Dot(w, direction) / Vec3::Dot(direction, direction);
    float r = Vec3::Mag(w - direction * alpha);
    if (0 <= alpha && alpha <= length) {
        cout << "in" << endl;
        return pair<Vec3, bool>(intersectedPoint, true);
    }
    return pair<Vec3, bool>(Vec3(0,0,0), false);
}