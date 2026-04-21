#ifndef RAY_H
#define RAY_H

#include "vector.h"

struct Ray {
    public:
        Vec3 origin;
        Vec3 raydir;
        Vec3 invRaydir;

        Vec3 GetRay(float t) const { return origin + raydir * t; }

        Ray(Vec3 origin, Vec3 raydir) : origin(origin), raydir(raydir), invRaydir(1/raydir.x, 1/raydir.y, 1/raydir.z) {}
}; 

struct HitRecord {
    public:
        Vec3 intersection = Vec3(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        float entryIntersection = std::numeric_limits<float>::infinity();
        float exitIntersection = std::numeric_limits<float>::infinity();
        int triangleHitIndex = -1;
};
#endif