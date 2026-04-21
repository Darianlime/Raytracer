#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "vector.h"
#include "models/geometry.h"

struct BoundingBox {
    public:

        Vec3 min;
        Vec3 max;
        Vec3 center;

        BoundingBox();
        Vec3 CalcCenter() const;
        Vec3 Size() const;
        Vec3 Size(Vec3 center) const;
        
        void GrowBox(Vec3& vertex);
        void GrowBoxTriangle(Triangle& tri);
        void ToString();
};

#endif