#ifndef BVH_H
#define BVH_H

#include "BoundingBox.h"
#include <vector>

struct BVHNode {
    BoundingBox bounds;
    std::vector<int> triangleIndexs;
    int leftChild = -1;
    int rightChild = -1;

    BVHNode() {};
    BVHNode(BoundingBox& bounds, const std::vector<int>& triangleIndexs) : bounds(bounds), triangleIndexs(triangleIndexs) {}
};

class BVH {
    private:
        std::vector<BVHNode> nodes;
        int leafSize;
        int triangleSize;
        const int MAX_DEPTH;
        void Split(BVHNode parent, int parentIndex, int depth);
    public:
        std::vector<Triangle> triangles;
        std::vector<Vec3> verts;

        BVH();
        BVH(int leafSize);
        void Init();
        void Build();
};

#endif