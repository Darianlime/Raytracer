#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include "color.h"
#include "ray.h"

struct Object {
    protected:
        string name;
    public:
        Vec3 pos;
        Color mat;

        Object() = default;
        Object(Vec3 pos, Color mat, string name);
        virtual ~Object() {};

        virtual pair<Vec3, bool> CheckIntersection(Ray ray) = 0;
        float GetHitDistance(float A, float B, float C); 
        string GetName() { return name; }

}; 

#endif