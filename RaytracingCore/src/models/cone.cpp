#include "models/cone.h"

Cone::Cone(Vec3 pos, Vec3 direction, float angle, float height, int mat, int tex) 
    : Model(pos, direction * M_PI / 180, Vec3(1,1,1), mat, tex, ModelType::CONE), angle(angle), direction(direction), height(height) {}

Cone::Cone(ConeData data)
    : Model(data.pos, data.direction * M_PI / 180, Vec3(1,1,1), data.mat, data.tex, ModelType::CONE), angle(data.angle), direction(data.direction), height(data.height) {}

Cone::Cone(vector<float> &args) 
    : Cone(ParseArgs(args)) {}

ConeData Cone::ParseArgs(vector<float> &args) {
    if (args.size() < 10) {
        std::cout << "created cone" << std::endl;
        return ConeData{Vec3(0.0f,1.0f,0.0f), Vec3(0.0f, -1.0f, 0.0f), 20.0f, 3.0f, -1, -1};
    }
    return ConeData{Vec3(args[0], args[1], args[2]), Vec3(args[3], args[4], args[5]), args[6], args[7], int(args[8]), int(args[9])};
}

bool Cone::CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection) {
    Vec3 localOrigin3 = (worldToLocal * Vec4(ray.origin)).toVec3();
    Vec3 localDir3 = (worldToLocal * Vec4(ray.raydir, 0.0f)).toVec3(); 

    Vec3 unitDir = Vec3(0, -1, 0);

    float cosA = cos(angle * M_PI / 180);
    float sinA = sin(angle * M_PI / 180);
    float A = pow(Vec3::Dot(localDir3, unitDir), 2) - pow(cosA, 2) * pow(localDir3.Mag(), 2);
    float B = 2 * (Vec3::Dot(localOrigin3, unitDir) * Vec3::Dot(localDir3, unitDir) - pow(cosA, 2) * Vec3::Dot(localOrigin3, localDir3));
    float C = pow(Vec3::Dot(localOrigin3, unitDir), 2) - pow(cosA, 2) *  pow(localOrigin3.Mag(), 2);

    pair<float, float> t = GetHitDistance(A, B, C);
    float tVal = t.first >= 0 ? t.first : t.second;
    if (tVal < 0) return false;

    float bestT = -1;

    Vec3 localHit = localDir3 * tVal + localOrigin3;
    float checkPoint = Vec3::Dot(localHit - Vec3(0,0,0), unitDir);
    if (0 <= checkPoint && checkPoint <= height) {
        bestT = tVal;
    }

    // Test cap
    Vec3 capCenter = unitDir * height;
    float denom = Vec3::Dot(localDir3, unitDir);
    if (fabs(denom) > 1e-6f) {
        float capT = Vec3::Dot(capCenter - localOrigin3, unitDir) / denom;
        if (capT >= 0) {
            Vec3 capHit = localDir3 * capT + localOrigin3;
            float capRadius = height * (sinA / cosA);
            if ((capHit - capCenter).Mag() <= capRadius) {
                if (bestT < 0 || capT < bestT) {
                    bestT = capT;
                }
            }
        }
    }

    if (bestT < 0) return false;

    entryIntersection = bestT;
    exitIntersection = t.second;
    
    intersection = (localToWorld * Vec4(localDir3 * bestT + localOrigin3)).toVec3();
    return true;
}

Vec3 Cone::GetNormal(Vec3 intersectedPoint, Vec3 raydir)
{
    Vec3 unitDir = Vec3(0, -1, 0);
    Vec3 local = (worldToLocal * Vec4(intersectedPoint)).toVec3();
    Matrix4 normalMatrix = worldToLocal.Transpose();

    float proj = Vec3::Dot(local, unitDir);

    // test cap
    Vec3 capCenter = unitDir * 1.0f;
    float capRadius = 1.0f;
    
    if (fabs(proj - 1.0f) < 1e-3f && (local - capCenter).Mag() <= capRadius + 1e-4f) {
        return (normalMatrix * Vec4(unitDir, 0)).toVec3().Normalize(); // cap normal in world space
    }

    // Otherwise cone surface normal
    Vec3 axisPoint = unitDir * proj;
    Vec3 radial = (local - axisPoint).Normalize();
    Vec3 localNormal = (radial * cos(angle * M_PI / 180) - unitDir * sin(angle * M_PI / 180)).Normalize();
    Vec3 worldNormal = (normalMatrix * Vec4(localNormal,0)).toVec3().Normalize();

    if (Vec3::Dot(worldNormal, raydir) < 0) {
        worldNormal = -worldNormal;
    }
    return worldNormal;
}

Vec2 Cone::GetTexUV(Vec3 intersectedPoint)
{
    return Vec2();
}

string Cone::GetName()
{
    return GetTypeMap()[type];
}