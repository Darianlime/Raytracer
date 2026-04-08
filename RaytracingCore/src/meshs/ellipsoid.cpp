#include "meshs/ellipsoid.h"

Ellipsoid::Ellipsoid(Vec3 pos, Vec3 radius, int mat) : Mesh(pos, mat, tex, MeshType::ELLIPSOID), radius(radius) {}

Ellipsoid::Ellipsoid(EllipsoidData data)
    : Mesh(data.pos, Vec3(0,0,0), data.radius, data.mat, data.tex, MeshType::ELLIPSOID), radius(data.radius) {}

Ellipsoid::Ellipsoid(vector<float> &args) 
    : Ellipsoid(ParseArgs(args)) {}

EllipsoidData Ellipsoid::ParseArgs(vector<float> &args) {
    if (args.size() < 8) {
        return EllipsoidData{Vec3(0,0,0), Vec3(1.0f,1.0f,1.0f), -1, -1};
    }
    return EllipsoidData{Vec3(args[0], args[1], args[2]), Vec3(args[3], args[4], args[5]), (int)args[6], int(args[7])};
}

bool Ellipsoid::CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection)
{
    float A = pow(ray.raydir.x, 2)/pow(size.x, 2) + pow(ray.raydir.y, 2)/pow(size.y, 2) + pow(ray.raydir.z, 2)/pow(size.z, 2);
    float B = 2 * ((ray.raydir.x * (ray.origin.x - pos.x)/pow(size.x, 2)) + (ray.raydir.y * (ray.origin.y - pos.y)/pow(size.y, 2)) + (ray.raydir.z * (ray.origin.z - pos.z)/pow(size.z, 2)));
    float C = pow(ray.origin.x - pos.x, 2)/pow(size.x, 2) + pow(ray.origin.y - pos.y, 2)/pow(size.y, 2) + pow(ray.origin.z - pos.z, 2)/pow(size.z, 2) - 1;

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

Vec3 Ellipsoid::GetNormal(Vec3 intersectedPoint, Vec3 raydir)
{
    // P is in world space, so shift to ellipsoid's local space first
    Vec3 local = intersectedPoint - pos;

    Vec3 normal(
        local.x / (size.x * size.x),
        local.y / (size.y * size.y),
        local.z / (size.z * size.z)
    );

    return normal.Normalize();
}

pair<float, float> Ellipsoid::GetTexUV(Vec3 intersectedPoint)
{
    return pair<float, float>();
}

string Ellipsoid::GetName()
{
    return GetTypeMap()[type];
}