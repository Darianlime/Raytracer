#include "models/mesh.h"
#include <limits>
#include <array>
using std::vector;
using std::numeric_limits;

Mesh::Mesh() : Model(Vec3(0,0,0), -1, -1, ModelType::MESH), name("Mesh") {}

Mesh::Mesh(std::string name, vector<int> args) : Model(Vec3(0,0,0), -1, -1, ModelType::MESH), name(name) {}

bool Mesh::CheckIntersection(Ray ray, HitRecord& hitRecord)
{
    if (bvh.triangles[hitRecord.triangleHitIndex].CheckIntersection(ray, hitRecord.entryIntersection, hitRecord.exitIntersection, hitRecord.intersection)) {
        return true;
    }    
    return false;
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