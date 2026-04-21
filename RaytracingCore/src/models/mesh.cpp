#include "models/mesh.h"
#include <limits>
#include <array>
using std::vector;
using std::numeric_limits;

Mesh::Mesh() : Model(Vec3(0,0,0), -1, -1, ModelType::MESH), name("Mesh") {}

Mesh::Mesh(std::string name, vector<int> args) : Model(Vec3(0,0,0), -1, -1, ModelType::MESH), name(name) {}

bool Mesh::CheckIntersection(const Ray& ray, HitRecord& hitRecord)
{
    return CheckBVHIntersection(ray, bvh.nodes[0], hitRecord.triangleHitIndex, hitRecord);
}

bool Mesh::CheckBVHIntersection(const Ray& ray, const BVHNode& node, const int ignoreTriangle, HitRecord& hitRecord)
{
    if (!BVH::IsBoundsHit(ray, node.bounds)) return false;

    bool hit = false;
    if (node.child == -1) {
        for (int triIndex : node.triangleIndexs) {
            if (ignoreTriangle == triIndex) continue;
            HitRecord newHit{};
            if (bvh.triangles[triIndex].CheckIntersection(ray, newHit.entryIntersection, newHit.exitIntersection, newHit.intersection)) {
                if (newHit.entryIntersection < hitRecord.entryIntersection) {
                    hitRecord.entryIntersection = newHit.entryIntersection;
                    hitRecord.exitIntersection = newHit.exitIntersection;
                    hitRecord.intersection = newHit.intersection;
                    hitRecord.triangleHitIndex = triIndex;
                    hit = true;
                }
            }   
        }
        return hit;
    } 
    bool hitL = CheckBVHIntersection(ray, bvh.nodes[node.child], ignoreTriangle, hitRecord);
    bool hitR = CheckBVHIntersection(ray, bvh.nodes[node.child + 1], ignoreTriangle, hitRecord);
    return hitL || hitR;
}

void Mesh::CenterOrgVertsToCenter() {
    for (auto& vertex : orignalVerts) {
		vertex = vertex - pos; 
    }
}

void Mesh::UpdateTransformation()
{
    SetMatrix(pos, rot * M_PI / 180, size);
    //Matrix4 normalMatrix = worldToLocal.Transpose();
    for (int i = 0; i < bvh.verts.size(); i++) {
        bvh.verts[i] = (localToWorld * Vec4(orignalVerts[i])).toVec3();
    }

    bvh.Build();
}

Vec3 Mesh::GetNormal(Vec3 intersectedPoint, Vec3 raydir)
{
    return currentNormal;
}

Vec2 Mesh::GetTexUV(Vec3 intersectedPoint)
{
    return currentTexture;
}

string Mesh::GetName()
{
    return name;
}