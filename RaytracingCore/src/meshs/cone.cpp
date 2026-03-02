#include "meshs/cone.h"

Cone::Cone(Vec3 pos, Vec3 direction, float angle, float height, int mat) 
    : Mesh(pos, mat, MeshType::CONE), angle(angle), direction(direction), height(height) {}

Cone::Cone(ConeData data)
    : Mesh(data.pos, data.mat, MeshType::CONE), angle(data.angle), direction(data.direction), height(data.height) {}

Cone::Cone(vector<float> &args) 
    : Cone(ParseArgs(args)) {}

ConeData Cone::ParseArgs(vector<float> &args) {
    if (args.size() < 8) {
        return ConeData{Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, -1.0f, 0.0f), 1.0f, 1.0f, 0};
    }
    return ConeData{Vec3(args[0], args[1], args[2]), Vec3(args[3], args[4], args[5]), args[6], args[7], int(args[8])};
}

pair<Vec3, bool> Cone::CheckIntersection(Ray ray) {
    Vec3 unitDir = direction / Vec3::Mag(direction);
    Vec3 point = ray.origin - pos;

    float A = pow(Vec3::Dot(ray.raydir, unitDir), 2) - pow(cos(angle * M_PI / 180), 2) * pow(Vec3::Mag(ray.raydir), 2);
    float B = 2 * (Vec3::Dot(point, unitDir) * Vec3::Dot(ray.raydir, unitDir) - pow(cos(angle * M_PI / 180), 2) * Vec3::Dot(point, ray.raydir));
    float C = pow(Vec3::Dot(point, unitDir), 2) - pow(cos(angle * M_PI / 180), 2) *  pow(Vec3::Mag(point), 2);

    float t = GetHitDistance(A, B, C);
    if (t < 0) {
        return pair<Vec3, bool>(Vec3(0,0,0), false);
    }
    
    Vec3 intersectedPoint = ray.GetRay(t);
    
    // Check if point lies between 0 and height
    float checkPoint = Vec3::Dot(intersectedPoint - pos, unitDir);
    if (0 <= checkPoint && checkPoint <= height) {
        return pair<Vec3, bool>(intersectedPoint, true);
    }
    return pair<Vec3, bool>(Vec3(0,0,0), false);
}

Vec3 Cone::GetNormal(Vec3 intersectedPoint)
{
    return Vec3();
}

string Cone::GetName()
{
    return GetTypeMap()[type];
}