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
    return Indices{args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]};
}

bool Triangle::CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection, vector<Vec3>& verts)
{
    //verts[indices.v1P].ToString();
    //verts[indices.v2P].ToString();
    //verts[indices.v3P].ToString();
    Vec3 e1 = verts[indices.v2P] - verts[indices.v1P];
    Vec3 e2 = verts[indices.v3P] - verts[indices.v1P];
    Vec3 n = Vec3::Cross(e1, e2); // normal vector of triangle
    normal = n.Normalize();
    
    float D = -(Vec3::Dot(n, verts[indices.v1P]));

    float denominator = Vec3::Dot(n, ray.raydir);
    if (fabs(denominator) < 1e-6) { return false; } 

    float t = -(Vec3::Dot(n, ray.origin) + D) / denominator;
    if (t < 0) {
        return false;
    }

    Vec3 intersectedPoint = ray.GetRay(t);
    Vec3 ep = intersectedPoint - verts[indices.v1P];

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
    if ((0 <= alpha && alpha <= 1) && (0 <= beta && beta <= 1) && (0 <= gamma && gamma <= 1))
    {
        entryIntersection = t;
        exitIntersection = t;
        intersection = intersectedPoint;
        return true;
    }
    return false;
}

Vec3 Triangle::GetNormal()
{
    return normal;
}

Vec2 Triangle::GetTexUV()
{
    return texture;
}

Indices Triangle::GetIndices() {
    return indices;
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
