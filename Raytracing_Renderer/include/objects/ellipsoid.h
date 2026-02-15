#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "object.h"

struct Ellipsoid : public Object {
    public:
        Vec3 radius;

        Ellipsoid() = default;
        Ellipsoid(Vec3 pos, Vec3 radius, Material mat);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;
}; 

#endif