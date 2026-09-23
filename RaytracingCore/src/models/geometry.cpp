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
}

bool Triangle::CheckIntersection(const Ray& ray, Vec3& baycentric, float& entryIntersection, float& exitIntersection, Vec3& intersection)
{
    const float EPS = 1e-6f;
    const float det = -Vec3::Dot(cachedNormal, ray.raydir);

    if (fabs(det) < EPS) { return false; }

    const float invDet = 1.0f / det;
    const Vec3 pvec = Vec3::Cross(ray.raydir, e2);
    const Vec3 tvec = ray.origin - v0;
    const float u = Vec3::Dot(tvec, pvec) * invDet;

    if (u < -EPS || u > 1.0f + EPS) { return false; }

    const Vec3 qvec = Vec3::Cross(tvec, e1);
    const float v = Vec3::Dot(ray.raydir, qvec) * invDet;

    if (v < -EPS || u + v > 1.0f + EPS) { return false; }

    const float t = Vec3::Dot(e2, qvec) * invDet;

    if (t < EPS) {return false; }

    entryIntersection = t;
    exitIntersection = t;
    baycentric = Vec3(1.0f - u - v, u, v);
    intersection = ray.GetRay(t);
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
