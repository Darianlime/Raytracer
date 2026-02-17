#include "shapes/ellipsoid.h"

Ellipsoid::Ellipsoid(Vec3 pos, Vec3 radius, int mat) : Shape(pos, mat, "ellipsoid"), radius(radius) {}

pair<Vec3, bool> Ellipsoid::CheckIntersection(Ray ray)
{
    float A = pow(ray.raydir.x, 2)/pow(radius.x, 2) + pow(ray.raydir.y, 2)/pow(radius.y, 2) + pow(ray.raydir.z, 2)/pow(radius.z, 2);
    float B = 2 * ((ray.raydir.x * (ray.origin.x - pos.x)/pow(radius.x, 2)) + (ray.raydir.y * (ray.origin.y - pos.y)/pow(radius.y, 2)) + (ray.raydir.z * (ray.origin.z - pos.z)/pow(radius.z, 2)));
    float C = pow(ray.origin.x - pos.x, 2)/pow(radius.x, 2) + pow(ray.origin.y - pos.y, 2)/pow(radius.y, 2) + pow(ray.origin.z - pos.z, 2)/pow(radius.z, 2) - 1;

    float t = GetHitDistance(A, B, C);
    if (t < 0) {
        return pair<Vec3, bool>(Vec3(0,0,0), false);
    }
    
    Vec3 intersectedPoint = ray.GetRay(t);
    return pair<Vec3, bool>(intersectedPoint, true);
}

Vec3 Ellipsoid::GetNormal(Vec3 intersectedPoint)
{
    return Vec3();
}