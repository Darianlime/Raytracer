#ifndef CYLINDER_H
#define CYLINDER_H

#include "object.h"

struct Cylinder : public Object {
    public:
        float radius;
        float length;
        Vec3 direction;

        Cylinder() = default;
        Cylinder(Vec3 pos, Vec3 direction, float radius, float length, Color mat);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
}; 

#endif