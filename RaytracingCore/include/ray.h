#ifndef RAY_H
#define RAY_H

#include "vector.h"

struct Ray {
    public:
        Vec3 origin;
        Vec3 raydir;

        Vec3 GetRay(float t) { return origin + raydir * t; }
}; 

#endif