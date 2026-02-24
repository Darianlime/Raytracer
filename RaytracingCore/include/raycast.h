#ifndef RAYCAST_H
#define RAYCAST_H

#include "vector.h"
#include "material.h"
#include "factory/ObjectFactory.h"
#include <vector>
#include <map>

namespace Raytracer {
class Raycast {
    private:
        Vec3 eye;
        Vec3 raydir;
    public:
        Raycast() = default;
        Raycast(Vec3 eye);

        Vec3 GetEye();
        void SetEye(Vec3 eye);
        Vec3 GetRayDir();
        void SetRayDir(Vec3 raydir);
        void SetRayDirAtPoint(Vec3 point);
        void SetRayDirAtPoint(Vec3 point, Vec3 eye);
        bool IsShadow(Light *light, Vec3 eye, Shape *intersectedShape, vector<Shape *> &shapes);
        Color TraceRay(Vec3 point, Color background, ObjectFactory &factories, pair<Vec3, bool> &intersectedPoint);
        Color ShadeRay(Shape *obj, vector<Material> mats, Vec3 intersectedPoint, vector<Shape *> shapes, vector<Light *> lights);
};
}
#endif