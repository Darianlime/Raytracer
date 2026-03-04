#include "meshs/geometry.h"

Triangle::Triangle(Indices indices, int mat) : Mesh(mat, MeshType::INDICE), indices(indices) {}

Triangle::Triangle(Indices data)
    : Mesh(mat, MeshType::INDICE), indices(data) {
    }

Triangle::Triangle(vector<float> & args) : Triangle(ParseArgs(args)) {}

Indices Triangle::ParseArgs(vector<float> &args) {
    Vec3 s = Vec3(args[0], args[1], args[2]);
    s.ToString();
    vector<Vertex> vertices(3);
    const int INDICE_SIZE = 8;
    for (int i = 0; i < vertices.size(); i++) {
        int index = i*INDICE_SIZE;
        vertices[i].pos = Vec3(args[index], args[index+1], args[index+2]);
        vertices[i].normal = Vec3(args[index+3], args[index+4], args[index+5]);
        vertices[i].texture = Vec2(args[index+6], args[index+7]);
    }
    mat = (int)args[args.size()-1];
    return Indices{vertices[0], vertices[1], vertices[2]};
}

pair<Vec3, bool> Triangle::CheckIntersection(Ray ray)
{
    Vec3 e1 = indices.v2.pos - indices.v1.pos;
    Vec3 e2 = indices.v3.pos - indices.v1.pos;
    Vec3 n = Vec3::Cross(e1, e2); // normal vector of triangle
    
    float D = -(Vec3::Dot(n, indices.v1.pos));

    float denominator = Vec3::Dot(n, ray.raydir);
    if (denominator == 0) { return pair<Vec3, bool>(Vec3(0,0,0), false); } 

    float t = -(Vec3::Dot(n, ray.origin) + D) / denominator;
    if (t < 0) {
        return pair<Vec3, bool>(Vec3(0,0,0), false);
    }

    Vec3 intersectedPoint = ray.GetRay(t);
    Vec3 ep = intersectedPoint - indices.v1.pos;

    float d11 = Vec3::Dot(e1, e1);
    float d12 = Vec3::Dot(e1, e2);
    float d22 = Vec3::Dot(e2, e2);
    float d1p = Vec3::Dot(e1, ep);
    float d2p = Vec3::Dot(e2, ep);

    float determinant = (d11 * d22) - (d12 * d12);
    if (determinant == 0) { return pair<Vec3, bool>(Vec3(0,0,0), false); }

    float beta = (d22*d1p - d12*d2p) / determinant;
    float gamma = (d11*d2p - d12*d1p) / determinant;
    float alpha = 1 - (beta + gamma);
    if ((0 <= alpha && alpha <= 1) && (0 <= beta && beta <= 1) && (0 <= gamma && gamma <= 1))
    {
        return pair<Vec3, bool>(intersectedPoint, true);
    }
    return pair<Vec3, bool>(Vec3(0,0,0), false);
}

Vec3 Triangle::GetNormal(Vec3 intersectedPoint)
{
    return Vec3();
}

string Triangle::GetName()
{
    return GetTypeMap()[type];
}