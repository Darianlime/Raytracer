#include "meshs/sphere.h"

Sphere::Sphere(Vec3 pos, float radius, int mat) 
    : Mesh(pos, mat, MeshType::SPHERE), radius(radius) {}

Sphere::Sphere(SphereData data)
    : Mesh(data.pos, data.mat, MeshType::SPHERE), radius(data.radius) {}

Sphere::Sphere(vector<float> &args) 
    : Sphere(ParseArgs(args)) {}

SphereData Sphere::ParseArgs(vector<float> &args) {
    if (args.size() < 4) {
        return SphereData{Vec3(0,0,0), 1.0f, 0};
    }
    return SphereData{Vec3(args[0], args[1], args[2]), args[3], (int)args[4]};
}

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

string Sphere::GetName()
{
    return GetTypeMap()[type];
}
