#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

struct Sphere : public Shape {
    public:
        float radius;

        Sphere() = default;
        Sphere(Vec3 pos, float radius, int mat);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;
}; 

#endif