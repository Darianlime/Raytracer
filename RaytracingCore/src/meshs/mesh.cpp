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

// returns the entry hit and exit hit
pair<float, float> Mesh::GetHitDistance(float A, float B, float C)
{
    float discriminant = pow(B, 2) - 4 * A * C;
    if (discriminant < 0) {
        return pair<float, float>(-1,-1);
    }

    float t1 = (-B - sqrt(discriminant)) / (2 * A); 
    float t2 = (-B + sqrt(discriminant)) / (2 * A); 

    if (t1 > t2) std::swap(t1, t2);

    if (t2 < 0) {
        return pair<float, float>(-1,-1);
    }
    if (t1 < 0) {
        t1 = 0.0f;
    }
    return pair<float, float>(t1, t2);
    
    // const float EPSILON = 1e-4f;
    // if ()
    // if (t1 > EPSILON) return t1;  // outside sphere, normal near hit
    // if (t2 > EPSILON) return t2;  // inside sphere, use far hit
}

map<MeshType, string> &Mesh::GetTypeMap() {
    return typeMap;
}

string Mesh::GetName()
{
    return "default shape";
}