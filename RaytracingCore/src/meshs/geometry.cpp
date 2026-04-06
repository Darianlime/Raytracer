#include "meshs/geometry.h"

Triangle::Triangle(Indices indices, int mat, int tex) : Mesh(mat, tex, MeshType::TRIANGLE), indices(indices) {}

Triangle::Triangle(Indices data)
    : Mesh(mat, tex, MeshType::TRIANGLE), indices(data) {
    }

Triangle::Triangle(vector<float> & args) : Triangle(ParseArgs(args)) {}

Indices Triangle::ParseArgs(vector<float> &args) {
    std::cout << "crash" << args.size() << std::endl;
    vector<Vertex> vertices(3);
    const int INDICE_SIZE = 8;
    if (args.size() < 27) {
        vertices[0].pos = Vec3(-1, 1, 0);
        vertices[0].normal = Vec3(0, 0, 0);
        vertices[0].texture = Vec2(0, 0);
        vertices[1].pos = Vec3(-1, -1, 0);
        vertices[1].normal = Vec3(0, 0, 0);
        vertices[1].texture = Vec2(0, 0);
        vertices[2].pos = Vec3(1, -1, 0);
        vertices[2].normal = Vec3(0, 0, 0);
        vertices[2].texture = Vec2(0, 0);
    } else {
        for (int i = 0; i < vertices.size(); i++) {
            int index = i*INDICE_SIZE;
            vertices[i].pos = Vec3(args[index], args[index+1], args[index+2]);
            vertices[i].normal = Vec3(args[index+3], args[index+4], args[index+5]);
            vertices[i].texture = Vec2(args[index+6], args[index+7]);
        }
    }
    mat = (int)args[args.size()-3];
    tex = (int)args[args.size()-2];
    shadeType = (int)args[args.size()-1];
    std::cout << shadeType << std::endl;
    return Indices{vertices[0], vertices[1], vertices[2]};
}

bool Triangle::CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection)
{
    Vec3 e1 = indices.v2.pos - indices.v1.pos;
    Vec3 e2 = indices.v3.pos - indices.v1.pos;
    Vec3 n = Vec3::Cross(e1, e2); // normal vector of triangle
    normal = n / n.Mag();
    
    float D = -(Vec3::Dot(n, indices.v1.pos));

    float denominator = Vec3::Dot(n, ray.raydir);
    if (fabs(denominator) < 1e-6) { return false; } 

    float t = -(Vec3::Dot(n, ray.origin) + D) / denominator;
    if (t < 0) {
        return false;
    }

    Vec3 intersectedPoint = ray.GetRay(t);
    Vec3 ep = intersectedPoint - indices.v1.pos;

    float d11 = Vec3::Dot(e1, e1);
    float d12 = Vec3::Dot(e1, e2);
    float d22 = Vec3::Dot(e2, e2);
    float d1p = Vec3::Dot(e1, ep);
    float d2p = Vec3::Dot(e2, ep);

    float determinant = (d11 * d22) - (d12 * d12);
    if (determinant == 0) { return false; }

    float beta = (d22*d1p - d12*d2p) / determinant;
    float gamma = (d11*d2p - d12*d1p) / determinant;
    float alpha = 1 - (beta + gamma);
    if (shadeType == (int)ShadeType::SMOOTH || shadeType == (int)ShadeType::SMOOTH_TEXTURED) {
        Vec3 pNormal = indices.v1.normal*alpha + indices.v2.normal*beta + indices.v3.normal*gamma;
        normal = pNormal.Normalize();
    }
    if (shadeType == (int)ShadeType::TEXTURED || shadeType == (int)ShadeType::SMOOTH_TEXTURED) {
        texture = indices.v1.texture*alpha + indices.v2.texture*beta + indices.v3.texture*gamma;
    }
    if ((0 <= alpha && alpha <= 1) && (0 <= beta && beta <= 1) && (0 <= gamma && gamma <= 1))
    {
        entryIntersection = t;
        exitIntersection = t;
        intersection = intersectedPoint;
        return true;
    }
    return false;
}

Vec3 Triangle::GetNormal(Vec3 intersectedPoint)
{
    return normal;
}

pair<float, float> Triangle::GetTexUV(Vec3 intersectedPoint)
{
    return pair<float, float>(texture.x, texture.y);
}

string Triangle::GetName()
{
    return GetTypeMap()[type];
}