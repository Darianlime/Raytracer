#include "models/cylinder.h"

Cylinder::Cylinder(Vec3 pos, Vec3 direction, float radius, float length, int mat) 
    : Model(pos, mat, tex, ModelType::CYLINDER), radius(radius), direction(direction), length(length) {}

Cylinder::Cylinder(CylinderData data)
    : Model(data.pos, data.mat, data.tex, ModelType::CYLINDER), radius(data.radius), direction(data.direction), length(data.length) {}

Cylinder::Cylinder(vector<float> &args) 
    : Cylinder(ParseArgs(args)) {}

CylinderData Cylinder::ParseArgs(vector<float> &args) {
    if (args.size() < 10) {
        return CylinderData{Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, -1.0f, 0.0f), 0.5f, 1.0f, -1, -1};
    }
    return CylinderData{Vec3(args[0], args[1], args[2]), Vec3(args[3], args[4], args[5]), args[6], args[7], int(args[8]), int(args[9])};
}

bool Cylinder::CheckIntersection(const Ray& ray, HitRecord& hitRecord) {
    Vec3 f = ray.origin - pos;
    float A = Vec3::Dot(ray.raydir, ray.raydir) - pow(Vec3::Dot(ray.raydir, direction),2);
    float B = 2 * (Vec3::Dot(ray.raydir, f) - Vec3::Dot(ray.raydir, direction) * Vec3::Dot(f, direction));
    float C = Vec3::Dot(f, f) - pow(Vec3::Dot(f, direction),2) - pow(radius,2);
    
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
    Vec3 w = hitRecord.intersection - pos;
    float alpha = Vec3::Dot(w, direction) / Vec3::Dot(direction, direction);
    if (0 <= alpha && alpha <= length) {
        return true;
    }
    return false;

}

Vec3 Cylinder::GetNormal(Vec3 intersectedPoint, Vec3 raydir)
{
    Vec3 unitDir = direction.Normalize();
    float proj = Vec3::Dot(intersectedPoint - pos, unitDir);
    Vec3 axisPoint = pos + unitDir * proj;

    return (intersectedPoint - axisPoint).Normalize();
}

Vec2 Cylinder::GetTexUV(Vec3 intersectedPoint)
{
    return Vec2();
}

string Cylinder::GetName()
{
    return GetTypeMap()[type];
}