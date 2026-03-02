#include "meshs/cylinder.h"

Cylinder::Cylinder(Vec3 pos, Vec3 direction, float radius, float length, int mat) 
    : Mesh(pos, mat, MeshType::CYLINDER), radius(radius), direction(direction), length(length) {}

Cylinder::Cylinder(CylinderData data)
    : Mesh(data.pos, data.mat, MeshType::CYLINDER), radius(data.radius), direction(data.direction), length(data.length) {}

Cylinder::Cylinder(vector<float> &args) 
    : Cylinder(ParseArgs(args)) {}

CylinderData Cylinder::ParseArgs(vector<float> &args) {
    if (args.size() < 8) {
        return CylinderData{Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, -1.0f, 0.0f), 1.0f, 1.0f, 0};
    }
    return CylinderData{Vec3(args[0], args[1], args[2]), Vec3(args[3], args[4], args[5]), args[6], args[7], int(args[8])};
}

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

Vec3 Cylinder::GetNormal(Vec3 intersectedPoint)
{
    return Vec3();
}

string Cylinder::GetName()
{
    return GetTypeMap()[type];
}