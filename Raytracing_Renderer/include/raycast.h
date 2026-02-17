#ifndef RAYCAST_H
#define RAYCAST_H

#include "vector.h"
#include "material.h"
#include "factory/ObjectFactory.h"
#include <vector>
#include <map>

class Raycast {
    private:
        Vec3 origin;
        Vec3 raydir;
    public:
        Raycast() = default;
        Raycast(Vec3 eye);

        Vec3 GetOrigin();
        Vec3 GetRayDir();
        void SetRayDir(Vec3 raydir);
        void SetRayDirAtPoint(Vec3 point);
        Vec3 GetRay(float t);
        Color TraceRay(Vec3 point, Color background, ObjectFactory& factories);
        Color ShadeRay(Shape *obj, vector<Material> mats, Vec3 intersectedPoint, vector<Light *> lights);
};

#endif