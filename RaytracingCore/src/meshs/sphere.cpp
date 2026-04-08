#include "meshs/sphere.h"

Sphere::Sphere(Vec3 pos, float radius, int mat) 
    : Mesh(pos, mat, tex, MeshType::SPHERE), radius(radius) {}

Sphere::Sphere(SphereData data)
    : Mesh(data.pos, Vec3(0,0,0), Vec3(data.radius, data.radius, data.radius), data.mat, data.tex, MeshType::SPHERE), radius(data.radius) {}

Sphere::Sphere(vector<float> &args) 
    : Sphere(ParseArgs(args)) {}

SphereData Sphere::ParseArgs(vector<float> &args) {
    if (args.size() < 6) {
        return SphereData{Vec3(0,0,0), 1.0f, -1, -1};
    }
    return SphereData{Vec3(args[0], args[1], args[2]), args[3], (int)args[4], (int)args[5]};
}

bool Sphere::CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection) {
    if (size.y != size.x && size.y != size.z) {
        size.x = size.y;
        size.z = size.y;
    } else if (size.z != size.x && size.z != size.y) {
        size.x = size.z;
        size.y = size.z;
    } else {
        size.y = size.x;
        size.z = size.x;
    }

    float A = pow(ray.raydir.x, 2) + pow(ray.raydir.y, 2) + pow(ray.raydir.z, 2);
    float B = 2 * (ray.raydir.x * (ray.origin.x - pos.x) + ray.raydir.y * (ray.origin.y - pos.y) + ray.raydir.z * (ray.origin.z - pos.z));
    float C = pow(ray.origin.x - pos.x, 2) + pow(ray.origin.y - pos.y, 2) + pow(ray.origin.z - pos.z, 2) - pow(size.x, 2);

    pair<float, float> t = GetHitDistance(A, B, C);
    if (t.first < 0 && t.second < 0) {
        return false;
    }
    entryIntersection = t.first;
    exitIntersection = t.second;
    intersection = ray.GetRay(entryIntersection);
    if (entryIntersection <= 0) {
        intersection = ray.GetRay(exitIntersection);
    }
    return true;
}

Vec3 Sphere::GetNormal(Vec3 intersectedPoint, Vec3 raydir)
{
    return (intersectedPoint - pos) / size.x;
}

pair<float, float> Sphere::GetTexUV(Vec3 intersectedPoint)
{
    float phi = acos((intersectedPoint.z - pos.z)/size.x);
    float theta = atan2(intersectedPoint.y - pos.y, intersectedPoint.x - pos.x);

    return pair<float, float>(std::max(theta/(2*M_PI), (theta + 2*M_PI)/(2*M_PI)), phi / M_PI);
}

string Sphere::GetName()
{
    return GetTypeMap()[type];
}
