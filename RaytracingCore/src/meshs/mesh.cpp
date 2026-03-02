#include "meshs/mesh.h"

map<MeshType, string> Mesh::typeMap = {
    {MeshType::SPHERE, "sphere"},
    {MeshType::CYLINDER, "cylinder"},
    {MeshType::CONE, "cone"},
    {MeshType::ELLIPSOID, "ellipsoid"},
    {MeshType::TRIANGLE, "triangle"},
    {MeshType::VERTEX, "v"},
    {MeshType::INDICE, "f"}
};

Mesh::Mesh(int mat, MeshType type) : mat(mat), type(type) {}
Mesh::Mesh(Vec3 pos, int mat, MeshType type) : Object(pos), mat(mat), type(type) {}

float Mesh::GetHitDistance(float A, float B, float C)
{
    float discriminant = pow(B, 2) - 4 * A * C;
    if (discriminant < 0) {
        return -1;
    }

    float t = (-B - sqrt(discriminant)) / (2 * A); 
    float t2 = (-B + sqrt(discriminant)) / (2 * A); 
    if (t < 0 && t2 < 0) {
        return -1;
    }
    if (t < 0 && t2 > 0) {
        t = t2;
    }
    if (t2 < t && t2 > 0) {
        t = t2;
    }
    return t;
}

map<MeshType, string> Mesh::GetTypeMap() {
    return typeMap;
}

string Mesh::GetName()
{
    return "default shape";
}