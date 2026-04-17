#include "models/model.h"

map<ModelType, string> Model::typeMap = {
    {ModelType::SPHERE, "sphere"},
    {ModelType::CYLINDER, "cylinder"},
    {ModelType::CONE, "cone"},
    {ModelType::ELLIPSOID, "ellipsoid"},
    {ModelType::MESH, "o"},
};

Model::Model(int mat, int tex, ModelType type) : mat(mat), tex(tex), type(type), lastVertIndex(-1), lastIndiceIndex(-1) {}
Model::Model(Vec3 pos, int mat, int tex, ModelType type) : Object(pos), mat(mat), tex(tex), type(type), lastVertIndex(-1), lastIndiceIndex(-1) {}
Model::Model(Vec3 pos, Vec3 rot, Vec3 size, int mat, int tex, ModelType type) : Object(pos, rot, size), mat(mat), tex(tex), type(type), lastVertIndex(-1), lastIndiceIndex(-1) {}

// returns the entry hit and exit hit
pair<float, float> Model::GetHitDistance(float A, float B, float C)
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

void Model::CalculateCentriod() {
    if (verts.empty()) return;
    for(auto& vert : verts) {
        pos = pos + vert;
    }
    pos = pos / verts.size();
}

std::vector<Vec3> &Model::GetVertices()
{
    return verts;
}

std::vector<Vec3> &Model::GetOrgVertices()
{
    return orignalVerts;
}

std::vector<Triangle> &Model::GetTriangles() {
    return triangles;
}

map<ModelType, string> &Model::GetTypeMap() {
    return typeMap;
}

string Model::GetName()
{
    return "default shape";
}