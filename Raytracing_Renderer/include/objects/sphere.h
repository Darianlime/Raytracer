#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

struct Sphere : public Object {
    public:
        float radius;

        Sphere() = default;
        Sphere(Vec3 pos, float radius, Material mat);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;
}; 

#endif