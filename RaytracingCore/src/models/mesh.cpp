#include "models/mesh.h"
#include <limits>
#include <array>
using std::vector;
using std::numeric_limits;

Mesh::Mesh() : Model(Vec3(0,0,0), -1, -1, ModelType::MESH), name("Mesh") {}

Mesh::Mesh(std::string name, vector<int> args) : Model(Vec3(0,0,0), args[0], args[1], ModelType::MESH), name(name) {}

bool Mesh::CheckIntersection(const Ray& ray, HitRecord& hitRecord)
{
    return CheckBVHIntersection(ray, bvh.nodes[0], hitRecord.triangleHitIndex, hitRecord);
}

bool Mesh::CheckBVHIntersection(const Ray& ray, const BVHNode& node, const int ignoreTriangle, HitRecord& hitRecord)
{
    // float nearestBoxHit = BVH::IsBoundsHit(ray, node.bounds);
    // if (!BVH::IsBoundsHit(ray, node.bounds)) return false;

    bool hit = false;
    if (node.child == -1) {
        for (int triIndex : node.triangleIndexs) {
            float nearestBoxHit = BVH::IsBoundsHit(ray, node.bounds);
            if (nearestBoxHit >= hitRecord.entryIntersection) return false;

            if (ignoreTriangle == triIndex) continue;
            HitRecord newHit{};
            if (bvh.triangles[triIndex].CheckIntersection(ray, newHit.baycentric, newHit.entryIntersection, newHit.exitIntersection, newHit.intersection)) {
                if (newHit.entryIntersection < hitRecord.entryIntersection) {
                    hitRecord.entryIntersection = newHit.entryIntersection;
                    hitRecord.exitIntersection = newHit.exitIntersection;
                    hitRecord.intersection = newHit.intersection;
                    hitRecord.triangleHitIndex = triIndex;
                    hitRecord.baycentric = newHit.baycentric;
                    hit = true;
                }
            }   
        }
        return hit;
    } 

    float nearestBoxHitL = BVH::IsBoundsHit(ray, bvh.nodes[node.child].bounds);
    float nearestBoxHitR = BVH::IsBoundsHit(ray, bvh.nodes[node.child + 1].bounds);
    bool hitL = false;
    bool hitR = false;

    if (nearestBoxHitL > nearestBoxHitR) {
        if (nearestBoxHitR < hitRecord.entryIntersection) {
            hitR = CheckBVHIntersection(ray, bvh.nodes[node.child + 1], ignoreTriangle, hitRecord);
        }
        if (nearestBoxHitL < hitRecord.entryIntersection) {
            hitL = CheckBVHIntersection(ray, bvh.nodes[node.child], ignoreTriangle, hitRecord);
        }
    } else {
        if (nearestBoxHitL < hitRecord.entryIntersection) {
            hitL = CheckBVHIntersection(ray, bvh.nodes[node.child], ignoreTriangle, hitRecord);
        }
        if (nearestBoxHitR < hitRecord.entryIntersection) {
            hitR = CheckBVHIntersection(ray, bvh.nodes[node.child + 1], ignoreTriangle, hitRecord);
        }
    }
    // dont prune child 
    // if (nearestBoxHit < hitRecord.entryIntersection) {
    //     hitL = CheckBVHIntersection(ray, bvh.nodes[node.child], ignoreTriangle, hitRecord);
    // }
    // if (nearestBoxHit < hitRecord.entryIntersection) {
    //     hitR = CheckBVHIntersection(ray, bvh.nodes[node.child + 1], ignoreTriangle, hitRecord);
    // }
    // // prune child box is further away from closest current intersection
    // if (nearestBoxHit >= hitRecord.entryIntersection) {
        
    // }
    //bool hitL = CheckBVHIntersection(ray, bvh.nodes[node.child], ignoreTriangle, hitRecord);
    //bool hitR = CheckBVHIntersection(ray, bvh.nodes[node.child + 1], ignoreTriangle, hitRecord);
    return hitL || hitR;
}

void Mesh::CenterOrgVertsToCenter() {
    for (auto& vertex : orignalVerts) {
		vertex.pos = vertex.pos - pos; 
    }
}

void Mesh::UpdateTransformation()
{
    SetMatrix(pos, rot * M_PI / 180, size);
    //Matrix4 normalMatrix = worldToLocal.Transpose();
    Matrix4 normalMatrix = localToWorld.InverseAffine().Transpose();

    for (int i = 0; i < bvh.verts.size(); i++) {
        bvh.verts[i].pos = (localToWorld * Vec4(orignalVerts[i].pos)).toVec3();
        Vec4 normal = normalMatrix * Vec4(orignalVerts[i].normal, 0.0f);
        bvh.verts[i].normal = normal.toVec3().Normalize();
    }
    bvh.Build();
}

Vec3 Mesh::GetNormal(Vec3 intersectedPoint, Vec3 raydir, const int triangleIndex)
{
    return GetTriangles()[triangleIndex].GetNormal(raydir).Normalize();
}

Vec2 Mesh::GetTexUV(Vec3 intersectedPoint)
{
    return currentTexture;
}

string Mesh::GetName()
{
    return name;
}