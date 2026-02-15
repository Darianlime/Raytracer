#ifndef RAYCAST_H
#define RAYCAST_H

#include "vector.h"
#include "material.h"
#include "objects/object.h"
#include "lights/light.h"
#include <vector>

class Raycast {
    private:
        Vec3 origin;
        Vec3 raydir;
    public:
        Raycast();
        Raycast(Vec3 eye);

        Vec3 GetOrigin();
        Vec3 GetRayDir();
        void SetRayDir(Vec3 raydir);
        void SetRayDirAtPoint(Vec3 point);
        Vec3 GetRay(float t);
        Color TraceRay(Vec3 point, Color background, vector<Object*> objects, vector<Light*> lights);
        Color ShadeRay(Object *obj, Vec3 intersectedPoint, vector<Light *> lights);
};

#endif