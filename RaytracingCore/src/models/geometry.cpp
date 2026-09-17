#include "models/geometry.h"
using std::vector;

Triangle::Triangle(Indices indices, int mat, int tex) : indices(indices) {}

Triangle::Triangle(Indices data) : indices(data) {}

Triangle::Triangle(vector<int> & args) : Triangle(ParseArgs(args)) {}

Indices Triangle::ParseArgs(vector<int> &args) {
    const int INDICE_SIZE = 8;
    // for (int i = 0; i < vertices.size(); i++) {
    //     int index = i*INDICE_SIZE;
    //     vertices[i].pos = Vec3(args[index], args[index+1], args[index+2]);
    //     vertices[i].normal = Vec3(args[index+3], args[index+4], args[index+5]);
    //     vertices[i].texture = Vec2(args[index+6], args[index+7]);
    // }
    mat = args[args.size()-3];
    //std::cout << "triangle mat: " << mat << std::endl; 
    tex = args[args.size()-2];
    shadeType = args[args.size()-1];
    //std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << " " << args[4] << " " << args[5] << " " << args[6] << " " << args[7] << " " << args[8] << std::endl;
    return Indices{};
}

void Triangle::CacheCalculations() {
    v0 = indices.v1->pos;
    e1 = indices.v2->pos - indices.v1->pos;
    e2 = indices.v3->pos - indices.v1->pos;
    cachedNormal = Vec3::Cross(e1, e2);
    cachedD = -(Vec3::Dot(cachedNormal, indices.v1->pos));
    d11 = Vec3::Dot(e1, e1);
    d12 = Vec3::Dot(e1, e2);
    d22 = Vec3::Dot(e2, e2);
    float determinant = d11 * d22 - d12 * d12;
    invDeterminant = 1.0f / determinant;
}

bool Triangle::CheckIntersection(const Ray& ray, Vec3& baycentric, float& entryIntersection, float& exitIntersection, Vec3& intersection)
{
    const float EPS = 1e-6f;
    
    float denominator = Vec3::Dot(cachedNormal, ray.raydir);
    if (fabs(denominator) < EPS) { return false; } 

    float t = -(Vec3::Dot(cachedNormal, ray.origin) + cachedD) / denominator;
    if (t < EPS) {
        return false;
    }

    Vec3 intersectedPoint = ray.GetRay(t);
    Vec3 ep = intersectedPoint - v0;

    float d1p = Vec3::Dot(e1, ep);
    float d2p = Vec3::Dot(e2, ep);

    float determinant = (d11 * d22) - (d12 * d12);
    if (determinant == 0) { return false; }

    float beta = (d22*d1p - d12*d2p) * invDeterminant;
    float gamma = (d11*d2p - d12*d1p) * invDeterminant;

    if (beta < -EPS || gamma < -EPS || beta + gamma > 1.0f + EPS) { return false; }

    float alpha = 1 - (beta + gamma);
    // if (shadeType == (int)ShadeType::SMOOTH || shadeType == (int)ShadeType::SMOOTH_TEXTURED) {
    //     Vec3 pNormal = verts[indices.v1N]*alpha + indices.v2.normal*beta + indices.v3.normal*gamma;
    //     normal = pNormal.Normalize();
    // }
    // if (shadeType == (int)ShadeType::TEXTURED || shadeType == (int)ShadeType::SMOOTH_TEXTURED) {
    //     texture = indices.v1.texture*alpha + indices.v2.texture*beta + indices.v3.texture*gamma;
    // }
    entryIntersection = t;
    exitIntersection = t;
    intersection = intersectedPoint;
    baycentric = Vec3(alpha, beta, gamma);
    return true;
}

Vec3 Triangle::CalcCenter()
{
    return (indices.v1->pos + indices.v1->pos + indices.v1->pos) / 3.0f;
}

Vec3 Triangle::GetNormal(const Vec3& viewDir)
{
    Vec3 normal = cachedNormal.Normalize();

    if (Vec3::Dot(cachedNormal, viewDir) > 0) {
        normal = -normal;
    }
    return normal;
}

Vec2 Triangle::GetTexUV()
{
    return Vec2();
}

Indices& Triangle::GetIndices() {
    return indices;
}

void Triangle::SetVertex(Vertex* vertex, int index) {
    if (index == 0) {
        indices.v1 = vertex;
        //indices.v1->ToString();
    } else if (index == 1) {
        indices.v2 = vertex;
        //indices.v2->ToString();
    } else if (index == 2) {
        indices.v3 = vertex;
        //indices.v3->ToString();
    } else {
        throw std::runtime_error("Runtime Error: Get vertex out of index");
    }
}

// void Triangle::SetNormals(int index, int normalIndex) {
//     if (index == 0) {
//         normals.v1 = normalIndex;
//         //indices.v1->ToString();
//     } else if (index == 1) {
//         normals.v2 = normalIndex;
//         //indices.v2->ToString();
//     } else if (index == 2) {
//         normals.v3 = normalIndex;
//         //indices.v3->ToString();
//     } else {
//         throw std::runtime_error("Runtime Error: Get normals out of index");
//     }
// }



// void Triangle::UpdateTransformation()
// {
//     SetMatrix(pos, rot * M_PI / 180, size);
//     //Matrix4 normalMatrix = worldToLocal.Transpose();

//     indices.v1.pos = (localToWorld * Vec4(originalIndices.v1.pos)).toVec3();
//     indices.v2.pos = (localToWorld * Vec4(originalIndices.v2.pos)).toVec3();
//     indices.v3.pos = (localToWorld * Vec4(originalIndices.v3.pos)).toVec3();
// }

// string Triangle::GetName()
// {
//     return "triangle";
// }
