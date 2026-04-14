#include "models/mesh.h"
#include <limits>
using std::vector;
using std::numeric_limits;

Mesh::Mesh() : pos(0,0,0), rotation(0,0,0), size(1,1,1), name("Mesh"), startIndice(-1), endIndice(-1) {}

Mesh::Mesh(std::string name, vector<int> args) : pos(0,0,0), rotation(0,0,0), size(1,1,1), name(name), startIndice(-1), endIndice(-1) {}

void Mesh::CalculateCentriod() {
    for(auto& vert : verts) {
        pos = pos + vert;
    }
    pos = pos / verts.size();
}

// bool Mesh::CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection)
// {
//     // float entryTriangle(numeric_limits<float>::infinity());
//     // float exitTriangle(numeric_limits<float>::infinity());
//     // Vec3 intersectionTriangle(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
//     // bool isIntersected = false;
//     // for (int i = 0; i < triangles.size(); i++) {
//     //     if (triangles[i].CheckIntersection(ray, entryTriangle, exitTriangle, intersectionTriangle, currentNormal, currentTexture)) {
//     //         if (entryTriangle > entryIntersection) {
//     //             entryIntersection = entryTriangle;
//     //             exitIntersection = entryTriangle;
//     //             intersection = intersectionTriangle;
//     //             isIntersected = true;
//     //         }
//     //     }
//     // }
//     // float closestDist(numeric_limits<float>::infinity());
//     // float entryTriangle{};
//     // float exitTriangle{};
//     // Vec3 intersectionTriangle(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
//     // bool isIntersected = false;
//     // for (int i = 0; i < triangles.size(); i++) {
//     //     if (triangles[i].CheckIntersection(ray, entryTriangle, exitTriangle, intersectionTriangle, currentNormal, currentTexture)) {
//     //         float dist = Vec3::Dist(ray.origin, intersectionTriangle);
//     //         const float EPSILON = 1e-4f;
//     //         if (dist > EPSILON && dist < closestDist) {
//     //             entryIntersection = entryTriangle;
//     //             exitIntersection = exitTriangle;
//     //             intersection = intersectionTriangle;
//     //             closestDist = dist;
//     //             isIntersected = true;
//     //         }
//     //     }
//     // }
//     // return isIntersected;
//     return false;
// }

// Vec3 Mesh::GetNormal(Vec3 intersectedPoint, Vec3 raydir)
// {
//     return currentNormal;
// }

// Vec2 Mesh::GetTexUV(Vec3 intersectedPoint)
// {
//     return currentTexture;
// }

string Mesh::GetName()
{
    return name;
}