#ifndef CONE_H
#define CONE_H

#include "shape.h"

struct Cone : public Shape {
    public:
        float angle;
        float height;
        Vec3 direction;

        Cone() = default;
        Cone(Vec3 pos, Vec3 direction, float angle, float height, int mat);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;
}; 

#endif