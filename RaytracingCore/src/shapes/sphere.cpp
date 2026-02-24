#include "shapes/sphere.h"

Sphere::Sphere(Vec3 pos, float radius, int mat) 
    : Shape(pos, mat, "sphere"), radius(radius) {}

pair<Vec3, bool> Sphere::CheckIntersection(Ray ray) {
    float A = pow(ray.raydir.x, 2) + pow(ray.raydir.y, 2) + pow(ray.raydir.z, 2);
    float B = 2 * (ray.raydir.x * (ray.origin.x - pos.x) + ray.raydir.y * (ray.origin.y - pos.y) + ray.raydir.z * (ray.origin.z - pos.z));
    float C = pow(ray.origin.x - pos.x, 2) + pow(ray.origin.y - pos.y, 2) + pow(ray.origin.z - pos.z, 2) - pow(radius, 2);

    float t = GetHitDistance(A, B, C);
    if (t < 0) {
        return pair<Vec3, bool>(Vec3(0,0,0), false);
    }
    
    Vec3 intersectedPoint = ray.GetRay(t);
    return pair<Vec3, bool>(intersectedPoint, true);
}

Vec3 Sphere::GetNormal(Vec3 intersectedPoint)
{
    return (intersectedPoint - pos) / radius;
}
