#ifndef RAYCAST_H
#define RAYCAST_H

#include "vector.h"
#include "color.h"

class Raycast {
    private:
        Vec3 origin;

        float dx;
        float dy;
        float dz;

        Vec3 raydir;
    public:
        Raycast();
        Raycast(Vec3 eye);

        Vec3 GetOrigin();
        Vec3 GetRayDir();
        void SetRayDir(Vec3 raydir);
        void SetRayDirAtPoint(Vec3 point);
        Vec3 GetRay(float t);
        Color TraceRay(Vec3 point, Color background);
}; 

#endif