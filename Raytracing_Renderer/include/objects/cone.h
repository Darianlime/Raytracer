#ifndef CONE_H
#define CONE_H

#include "object.h"

struct Cone : public Object {
    public:
        float angle;
        float height;
        Vec3 direction;

        Cone() = default;
        Cone(Vec3 pos, Vec3 direction, float angle, float height, Material mat);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;
}; 

#endif