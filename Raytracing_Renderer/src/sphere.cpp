#include "objects/sphere.h"

Sphere::Sphere(Vec3 pos, float radius, Color mat) 
    : Object(pos, mat, "sphere"), radius(radius) {}

pair<Vec3, bool> Sphere::CheckIntersection(Ray ray) {
    float A = pow(ray.raydir.x, 2) + pow(ray.raydir.y, 2) + pow(ray.raydir.z, 2);
    float B = 2 * (ray.raydir.x * (ray.origin.x - pos.x) + ray.raydir.y * (ray.origin.y - pos.y) + ray.raydir.z * (ray.origin.z - pos.z));
    float C = pow(ray.origin.x - pos.x, 2) + pow(ray.origin.y - pos.y, 2) + pow(ray.origin.z - pos.z, 2) - pow(radius, 2);
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
    return pair<Vec3, bool>(intersectedPoint, true);
}
