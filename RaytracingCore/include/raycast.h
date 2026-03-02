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
    public:
        Raycast() = default;
        Raycast(Vec3 eye);

        Vec3 GetEye();
        void SetEye(Vec3 eye);
        Vec3 CalcRayDirAtPoint(Vec3 point) const;
        Vec3 CalcRayDirAtPoint(Vec3 point, Vec3 intersectedPoint) const;
        bool IsShadow(Light *light, Vec3 eye, Mesh *intersectedShape, vector<Mesh *> &shapes);
        Color TraceRay(Vec3 point, Color background, ObjectFactory &factories, pair<Vec3, bool> &intersectedPoint);
        Color ShadeRay(Mesh *obj, Material mat, Vec3 intersectedPoint, vector<Mesh *> shapes, vector<Light *> lights);
};
}
#endif