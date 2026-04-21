#include "BVH/BVH.h"
#include <numeric>
using std::vector;

BVH::BVH() : leafSize(4), MAX_DEPTH(64) {}

BVH::BVH(int leafSize) : leafSize(leafSize), MAX_DEPTH(64) {}

void BVH::Init() {
    triangleSize = triangles.size();
    nodes.reserve((triangleSize / leafSize) * 2);
}

void BVH::Build()
{
    BoundingBox bounds;

    // expand bounds to mesh
    for (Vec3 vert : verts) {
        bounds.GrowBox(vert);
    }

    bounds.ToString();

    // fills index from 0, 1, 2 to triangleSize
    vector<int> triangleIndex(triangleSize);
    std::iota(triangleIndex.begin(), triangleIndex.end(), 0); 

    nodes.emplace_back(bounds, triangleIndex);

    Split(nodes[0], 0, 0);
}

void BVH::Split(const BVHNode& parent, int parentIndex, int depth = 0) {
    if (parent.triangleIndexs.size() <= leafSize || depth >= MAX_DEPTH) {
        return;
    }
    Vec3 center = parent.bounds.CalcCenter();
    Vec3 size = parent.bounds.Size(center);
    int axis = 0;
    if (size.y > size.x) axis = 1;
    if (size.z > size.GetAxisValue(axis)) axis = 2;
    float centerAxis = center.GetAxisValue(axis);

    int left = nodes.size();
    int right = nodes.size() + 1;
    nodes.emplace_back();
    nodes.emplace_back();

    for (int triIndex : parent.triangleIndexs) {
        Triangle& tri = triangles[triIndex];
        float triAxis = tri.CalcCenter().GetAxisValue(axis);
        int inLeftBox = triAxis < centerAxis ? left : right;
        nodes[inLeftBox].triangleIndexs.emplace_back(triIndex);
        nodes[inLeftBox].bounds.GrowBoxTriangle(tri);
    }
    
    if (nodes[left].triangleIndexs.empty() || nodes[right].triangleIndexs.empty()) {
        return;
    }
    // std::cout << "split: ";
    // for (int i : nodes[left].triangleIndexs) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "split: ";
    // for (int i : nodes[right].triangleIndexs) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;

    nodes[parentIndex].child = left;

    Split(nodes[left], left, depth + 1);
    Split(nodes[right], right, depth + 1);
}

bool BVH::IsBoundsHit(const Ray& ray, const BoundingBox& bounds)
{
    float tx1 = (bounds.min.x - ray.origin.x) * ray.invRaydir.x;
    float tx2 = (bounds.max.x - ray.origin.x) * ray.invRaydir.x;

    float tmin = fminf(tx1, tx2);
    float tmax = fmaxf(tx1, tx2);

    float ty1 = (bounds.min.y - ray.origin.y) * ray.invRaydir.y;
    float ty2 = (bounds.max.y - ray.origin.y) * ray.invRaydir.y;

    tmin = fmaxf(tmin, fminf(ty1, ty2));
    tmax = fminf(tmax, fmaxf(ty1, ty2));

    float tz1 = (bounds.min.z - ray.origin.z) * ray.invRaydir.z;
    float tz2 = (bounds.max.z - ray.origin.z) * ray.invRaydir.z;

    tmin = fmaxf(tmin, fminf(tz1, tz2));
    tmax = fminf(tmax, fmaxf(tz1, tz2));

    return tmax >= tmin && tmax > 0.0f;
}

