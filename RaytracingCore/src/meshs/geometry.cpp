#include "meshs/geometry.h"

Triangle::Triangle(Indices indices, int mat) : Mesh(mat, MeshType::TRIANGLE), indices(indices) {}

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