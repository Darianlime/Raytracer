#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "vector.h"
#include "models/geometry.h"

struct BoundingBox {
    private:
        Vec3 min;
        Vec3 max;
        Vec3 center;
    public:
        BoundingBox();
        Vec3 CalcCenter();
        Vec3 Size();
        Vec3 Size(Vec3 center);
        void GrowBox(Vec3& vertex);
        void GrowBoxTriangle(Triangle& tri);
        void ToString();
};

#endif