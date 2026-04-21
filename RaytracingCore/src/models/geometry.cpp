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
    return Indices{nullptr, nullptr, nullptr};
}

bool Triangle::CheckIntersection(const Ray& ray, float& entryIntersection, float& exitIntersection, Vec3& intersection)
{
    const float EPS = 1e-6f;
    //verts[indices.v1P].ToString();
    //verts[indices.v2P].ToString();
    Vec3 ind1 = *indices.v1; 
    Vec3 ind2 = *indices.v2;
    Vec3 ind3 = *indices.v3;
    Vec3 e1 = ind2 - ind1;
    Vec3 e2 = ind3 - ind1;
    Vec3 n = Vec3::Cross(e1, e2); // normal vector of triangle
    normal = n.Normalize();
    
    float D = -(Vec3::Dot(n, ind1));

    float denominator = Vec3::Dot(n, ray.raydir);
    if (fabs(denominator) < EPS) { return false; } 

    float t = -(Vec3::Dot(n, ray.origin) + D) / denominator;
    if (t < EPS) {
        return false;
    }

    Vec3 intersectedPoint = ray.GetRay(t);
    Vec3 ep = intersectedPoint - ind1;

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
    // if (shadeType == (int)ShadeType::SMOOTH || shadeType == (int)ShadeType::SMOOTH_TEXTURED) {
    //     Vec3 pNormal = verts[indices.v1N]*alpha + indices.v2.normal*beta + indices.v3.normal*gamma;
    //     normal = pNormal.Normalize();
    // }
    // if (shadeType == (int)ShadeType::TEXTURED || shadeType == (int)ShadeType::SMOOTH_TEXTURED) {
    //     texture = indices.v1.texture*alpha + indices.v2.texture*beta + indices.v3.texture*gamma;
    // }
    if ((alpha >= -EPS && alpha <= 1 + EPS) && (beta  >= -EPS && beta <= 1 + EPS) && (gamma >= -EPS && gamma <= 1 + EPS))
    {
        entryIntersection = t;
        exitIntersection = t;
        intersection = intersectedPoint;
        return true;
    }
    return false;
}

Vec3 Triangle::CalcCenter()
{
    return (*indices.v1 + *indices.v2 + *indices.v3) / 3.0f;
}

Vec3 Triangle::GetNormal()
{
    return normal;
}

Vec2 Triangle::GetTexUV()
{
    return texture;
}

Indices& Triangle::GetIndices() {
    return indices;
}

void Triangle::SetIndice(int index, Vec3* vert) {
    if (index == 0) {
        indices.v1 = vert;
        //indices.v1->ToString();
    } else if (index == 1) {
        indices.v2 = vert;
        //indices.v2->ToString();
    } else if (index == 2) {
        indices.v3 = vert;
        //indices.v3->ToString();
    } else {
        throw std::runtime_error("Runtime Error: Get indices out of index");
    }
}



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
