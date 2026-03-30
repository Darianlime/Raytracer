#include "meshs/cone.h"

Cone::Cone(Vec3 pos, Vec3 direction, float angle, float height, int mat, int tex) 
    : Mesh(pos, mat, tex, MeshType::CONE), angle(angle), direction(direction), height(height) {}

Cone::Cone(ConeData data)
    : Mesh(data.pos, data.mat, data.tex, MeshType::CONE), angle(data.angle), direction(data.direction), height(data.height) {}

Cone::Cone(vector<float> &args) 
    : Cone(ParseArgs(args)) {}

ConeData Cone::ParseArgs(vector<float> &args) {
    if (args.size() < 10) {
        return ConeData{Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, -1.0f, 0.0f), 1.0f, 1.0f, -1, -1};
    }
    return ConeData{Vec3(args[0], args[1], args[2]), Vec3(args[3], args[4], args[5]), args[6], args[7], int(args[8]), int(args[9])};
}

bool Cone::CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection) {
    Vec3 unitDir = direction / direction.Mag();
    Vec3 point = ray.origin - pos;

    float A = pow(Vec3::Dot(ray.raydir, unitDir), 2) - pow(cos(angle * M_PI / 180), 2) * pow(ray.raydir.Mag(), 2);
    float B = 2 * (Vec3::Dot(point, unitDir) * Vec3::Dot(ray.raydir, unitDir) - pow(cos(angle * M_PI / 180), 2) * Vec3::Dot(point, ray.raydir));
    float C = pow(Vec3::Dot(point, unitDir), 2) - pow(cos(angle * M_PI / 180), 2) *  pow(point.Mag(), 2);

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
    
    // Check if point lies between 0 and height
    float checkPoint = Vec3::Dot(intersection - pos, unitDir);
    if (0 <= checkPoint && checkPoint <= height) {
        return true;
    }
    return false;
}

Vec3 Cone::GetNormal(Vec3 intersectedPoint)
{
    return Vec3();
}

pair<float, float> Cone::GetTexUV(Vec3 intersectedPoint)
{
    return pair<float, float>();
}

string Cone::GetName()
{
    return GetTypeMap()[type];
}