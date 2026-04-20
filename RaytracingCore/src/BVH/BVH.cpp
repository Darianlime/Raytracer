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

void BVH::Split(BVHNode parent, int parentIndex, int depth = 0) {
    if (parent.triangleIndexs.size() <= leafSize || depth >= MAX_DEPTH) {
        return;
    }
    Vec3 center = parent.bounds.CalcCenter();
    Vec3 size = parent.bounds.Size(center);
    int axis = size.x >= std::max(size.y, size.z) ? 0 : size.y >= size.z ? 1 : 2;
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

    nodes[parentIndex].leftChild = left;
    nodes[parentIndex].rightChild = right;

    Split(nodes[left], left, depth++);
    Split(nodes[right], right, depth++);
}

