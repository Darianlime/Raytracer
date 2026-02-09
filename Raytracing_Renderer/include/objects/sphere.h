#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

struct Sphere : public Object {
    public:
        float radius;

        Sphere() = default;
        Sphere(Vec3 pos, float radius, Color mat);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
}; 

#endif