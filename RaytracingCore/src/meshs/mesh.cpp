#include "meshs/mesh.h"

map<MeshType, string> Mesh::typeMap = {
    {MeshType::SPHERE, "sphere"},
    {MeshType::CYLINDER, "cylinder"},
    {MeshType::CONE, "cone"},
    {MeshType::ELLIPSOID, "ellipsoid"},
    {MeshType::TRIANGLE, "f"},
};

Mesh::Mesh(int mat, int tex, MeshType type) : mat(mat), tex(tex), type(type) {}
Mesh::Mesh(Vec3 pos, int mat, int tex, MeshType type) : Object(pos), mat(mat), tex(tex), type(type) {}
Mesh::Mesh(Vec3 pos, Vec3 rot, Vec3 size, int mat, int tex, MeshType type) : Object(pos, rot, size), mat(mat), tex(tex), type(type) {}

float Mesh::GetHitDistance(float A, float B, float C)
{
    float discriminant = pow(B, 2) - 4 * A * C;
    if (discriminant < 0) {
        return -1;
    }

    float t1 = (-B - sqrt(discriminant)) / (2 * A); 
    float t2 = (-B + sqrt(discriminant)) / (2 * A); 

    const float EPSILON = 1e-4f;
    if (t1 > EPSILON) return t1;  // outside sphere, normal near hit
    if (t2 > EPSILON) return t2;  // inside sphere, use far hit
    return -1;
}

map<MeshType, string> &Mesh::GetTypeMap() {
    return typeMap;
}

string Mesh::GetName()
{
    return "default shape";
}