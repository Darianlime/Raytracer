#include "models/mesh.h"
#include <limits>
using std::vector;
using std::numeric_limits;

Mesh::Mesh() : Model(Vec3(0,0,0), -1, -1, ModelType::MESH), name("Mesh") {}

Mesh::Mesh(std::string name, vector<int> args) : Model(Vec3(0,0,0), -1, -1, ModelType::MESH), name(name) {}

void Mesh::CalculateCentriod() {
    for(auto& vert : verts) {
        pos = pos + vert;
    }
    pos = pos / verts.size();
}

bool Mesh::CheckIntersection(Ray ray, HitRecord& hitRecord)
{
    if (triangles[hitRecord.triangleHitIndex].CheckIntersection(ray, hitRecord.entryIntersection, hitRecord.exitIntersection, hitRecord.intersection)) {
        return true;
    }    
    return false;
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