#include "vector.h"
#include "color.h"

#ifndef RAYCAST_H
#define RAYCAST_H

class Raycast {
    private:
        Vec3 pos;

        float dx;
        float dy;
        float dz;

        Vec3 raydir;
    public:
        Raycast();
        Raycast(Vec3 eye);

        void SetRayDir(Vec3 point);
        Vec3 GetRay(float t);
        Color TraceRay();
}; 

#endif