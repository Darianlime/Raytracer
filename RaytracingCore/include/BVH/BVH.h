#ifndef BVH_H
#define BVH_H

#include "BoundingBox.h"
#include <vector>

struct BVHNode {
    BoundingBox bounds;
    std::vector<int> triangleIndexs;
    int child = -1;

    BVHNode() {};
    BVHNode(BoundingBox& bounds, const std::vector<int>& triangleIndexs) : bounds(bounds), triangleIndexs(triangleIndexs) {}
};

class BVH {
    private:
        int leafSize;
        int triangleSize;
        const int MAX_DEPTH;
        void Split(const BVHNode &parent, int parentIndex, int depth);
    public:
        std::vector<BVHNode> nodes;
        std::vector<Triangle> triangles;
        std::vector<Vec3> verts;

        BVH();
        BVH(int leafSize);
        void Init();
        void Build();
        static bool IsBoundsHit(const Ray &ray, const BoundingBox &bounds);
};

#endif