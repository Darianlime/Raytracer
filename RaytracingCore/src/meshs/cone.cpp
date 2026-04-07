#include "meshs/cone.h"

Cone::Cone(Vec3 pos, Vec3 direction, float angle, float height, int mat, int tex) 
    : Mesh(pos, Vec3(direction.x * 180 / M_PI, direction.y * 180 / M_PI, direction.z * 180 / M_PI), Vec3(1,1,1), mat, tex, MeshType::CONE), angle(angle), direction(direction), height(height) {}

Cone::Cone(ConeData data)
    : Mesh(data.pos, Vec3(data.direction.x * 180 / M_PI, data.direction.y * 180 / M_PI, data.direction.z * 180 / M_PI), Vec3(1,1,1), data.mat, data.tex, MeshType::CONE), angle(data.angle), direction(data.direction), height(data.height) {}

Cone::Cone(vector<float> &args) 
    : Cone(ParseArgs(args)) {}

ConeData Cone::ParseArgs(vector<float> &args) {
    if (args.size() < 10) {
        std::cout << "created cone" << std::endl;
        return ConeData{Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, -1.0f, 0.0f), 20.0f, 6.0f, -1, -1};
    }
    return ConeData{Vec3(args[0], args[1], args[2]), Vec3(args[3], args[4], args[5]), args[6], args[7], int(args[8]), int(args[9])};
}

bool Cone::CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection) {
    direction.x = rot.x * M_PI / 180;
    direction.y = rot.y * M_PI / 180;
    direction.z = rot.z * M_PI / 180;

    Vec3 unitDir = direction.Normalize();
    Vec3 point = ray.origin - pos;
    float cosA = cos(angle * M_PI / 180);
    float sinA = sin(angle * M_PI / 180);

    float A = pow(Vec3::Dot(ray.raydir, unitDir), 2) - pow(cos(angle * M_PI / 180), 2) * pow(ray.raydir.Mag(), 2);
    float B = 2 * (Vec3::Dot(point, unitDir) * Vec3::Dot(ray.raydir, unitDir) - pow(cos(angle * M_PI / 180), 2) * Vec3::Dot(point, ray.raydir));
    float C = pow(Vec3::Dot(point, unitDir), 2) - pow(cos(angle * M_PI / 180), 2) *  pow(point.Mag(), 2);

    pair<float, float> t = GetHitDistance(A, B, C);
    float tVal = t.first >= 0 ? t.first : t.second;
    if (tVal < 0) return false;

     float bestT = -1;

    Vec3 intersectedPoint = ray.GetRay(tVal);
    float checkPoint = Vec3::Dot(intersectedPoint - pos, unitDir);
    if (0 <= checkPoint && checkPoint <= height) {
        entryIntersection = tVal;
        exitIntersection = t.second;
        intersection = intersectedPoint;
        bestT = entryIntersection;
    }

    // Test cap
    Vec3 capCenter = pos + unitDir * height;
    float denom = Vec3::Dot(ray.raydir, unitDir);
    if (fabs(denom) > 1e-6f) {
        float capT = Vec3::Dot(capCenter - ray.origin, unitDir) / denom;
        if (capT >= 0) {
            Vec3 capHit = ray.GetRay(capT);
            float capRadius = height * (sinA / cosA); 
            float distFromAxis = (capHit - capCenter).Mag();
            if (distFromAxis <= capRadius) {
                if (bestT < 0 || capT < bestT) {
                    bestT = capT;
                    intersection = capHit;
                }
            }
        }
    }

    if (bestT < 0) return false;

    entryIntersection = bestT;
    exitIntersection = t.second;
    
    return true;
}

Vec3 Cone::GetNormal(Vec3 intersectedPoint)
{
    Vec3 unitDir = direction.Normalize();
    Vec3 capCenter = pos + unitDir * height;

    float capRadius = height * tan(angle * M_PI / 180);
    float distFromAxis = (intersectedPoint - capCenter).Mag();

    // If P is on the cap
    if (distFromAxis <= capRadius + 1e-4f) {
        float proj = Vec3::Dot(intersectedPoint - pos, unitDir);
        if (fabs(proj - height) < 1e-3f)
            return unitDir; // flat cap normal
    }

    // Otherwise cone surface normal
    float proj = Vec3::Dot(intersectedPoint - pos, unitDir);
    Vec3 axisPoint = pos + unitDir * proj;
    Vec3 radial = (intersectedPoint - axisPoint).Normalize();
    return (radial * cos(angle * M_PI / 180) - unitDir * sin(angle * M_PI / 180)).Normalize();
}

pair<float, float> Cone::GetTexUV(Vec3 intersectedPoint)
{
    return pair<float, float>();
}

string Cone::GetName()
{
    return GetTypeMap()[type];
}