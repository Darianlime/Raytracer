#ifndef RAY_H
#define RAY_H

#include "vector.h"

struct Ray {
    public:
        Vec3 origin;
        Vec3 raydir;

        Vec3 GetRay(float t) { return origin + raydir * t; }
}; 

struct HitRecord {
    public:
        Vec3 intersection = Vec3(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        float entryIntersection = 0;
        float exitIntersection = 0;
        int triangleHitIndex = -1;
};
#endif