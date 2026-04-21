#include "models/sphere.h"

Sphere::Sphere(Vec3 pos, float radius, int mat) 
    : Model(pos, mat, tex, ModelType::SPHERE), radius(radius) {}

Sphere::Sphere(SphereData data)
    : Model(data.pos, Vec3(0,0,0), Vec3(data.radius, data.radius, data.radius), data.mat, data.tex, ModelType::SPHERE), radius(data.radius) {}

Sphere::Sphere(vector<float> &args) 
    : Sphere(ParseArgs(args)) {}

SphereData Sphere::ParseArgs(vector<float> &args) {
    if (args.size() < 6) {
        return SphereData{Vec3(0,0,0), 1.0f, -1, -1};
    }
    return SphereData{Vec3(args[0], args[1], args[2]), args[3], (int)args[4], (int)args[5]};
}

bool Sphere::CheckIntersection(const Ray& ray, HitRecord& hitRecord) {
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
    hitRecord.entryIntersection = t.first;
    hitRecord.exitIntersection = t.second;
    hitRecord.intersection = ray.GetRay(hitRecord.entryIntersection);
    if (hitRecord.entryIntersection <= 0) {
        hitRecord.intersection = ray.GetRay(hitRecord.exitIntersection);
    }
    return true;
}

Vec3 Sphere::GetNormal(Vec3 intersectedPoint, Vec3 raydir, const int triangleIndex)
{
    return (intersectedPoint - pos) / size.x;
}

Vec2 Sphere::GetTexUV(Vec3 intersectedPoint)
{
    float phi = acos((intersectedPoint.z - pos.z)/size.x);
    float theta = atan2(intersectedPoint.y - pos.y, intersectedPoint.x - pos.x);

    return Vec2(std::max(theta/(2*M_PI), (theta + 2*M_PI)/(2*M_PI)), phi / M_PI);
}

string Sphere::GetName()
{
    return GetTypeMap()[type];
}
