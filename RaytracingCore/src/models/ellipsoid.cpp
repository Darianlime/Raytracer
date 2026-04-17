#include "models/ellipsoid.h"

Ellipsoid::Ellipsoid(Vec3 pos, Vec3 radius, int mat) : Model(pos, mat, tex, ModelType::ELLIPSOID), radius(radius) {}

Ellipsoid::Ellipsoid(EllipsoidData data)
    : Model(data.pos, Vec3(0,0,0), data.radius, data.mat, data.tex, ModelType::ELLIPSOID), radius(data.radius) {}

Ellipsoid::Ellipsoid(vector<float> &args) 
    : Ellipsoid(ParseArgs(args)) {}

EllipsoidData Ellipsoid::ParseArgs(vector<float> &args) {
    if (args.size() < 8) {
        return EllipsoidData{Vec3(0,0,0), Vec3(1.0f,1.0f,1.0f), -1, -1};
    }
    return EllipsoidData{Vec3(args[0], args[1], args[2]), Vec3(args[3], args[4], args[5]), (int)args[6], int(args[7])};
}

bool Ellipsoid::CheckIntersection(Ray ray, HitRecord& hitRecord)
{
    Vec3 localOrigin = (worldToLocal * Vec4(ray.origin, 1.0f)).toVec3();
    Vec3 localDir = (worldToLocal * Vec4(ray.raydir, 0.0f)).toVec3();

    float A = localDir.x * localDir.x + localDir.y * localDir.y + localDir.z * localDir.z;
    float B = 2 * (localOrigin.x * localDir.x + localOrigin.y * localDir.y + localOrigin.z * localDir.z);
    float C = localOrigin.x * localOrigin.x + localOrigin.y * localOrigin.y + localOrigin.z * localOrigin.z - 1;

    pair<float, float> t = GetHitDistance(A, B, C);
    if (t.first < 0 && t.second < 0) return false;

    float tVal = t.first >= 0 ? t.first : t.second;

    hitRecord.entryIntersection = tVal;
    hitRecord.exitIntersection  = t.second;

    hitRecord.intersection = (localToWorld * Vec4(localOrigin + localDir * tVal, 1.0f)).toVec3();
    return true;
}

Vec3 Ellipsoid::GetNormal(Vec3 intersectedPoint, Vec3 raydir)
{
    Vec3 local = (worldToLocal * Vec4(intersectedPoint, 1.0f)).toVec3();

    Matrix4 normalMatrix = worldToLocal.Transpose();
    return (normalMatrix * Vec4(local, 0.0f)).toVec3().Normalize();
}

Vec2 Ellipsoid::GetTexUV(Vec3 intersectedPoint)
{
    return Vec2();
}

string Ellipsoid::GetName()
{
    return GetTypeMap()[type];
}