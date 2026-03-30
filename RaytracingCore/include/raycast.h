#ifndef RAYCAST_H
#define RAYCAST_H

#include "vector.h"
#include "material.h"
#include "factory/ObjectFactory.h"
#include <vector>
#include <map>

namespace Raytracer {

struct RayHit {
    bool hit;
    Mesh* mesh;
    Material mat; 
    Vec3 intersectedPoint;
    Vec3 viewDir;
    float t; // beers law distance between entry and exit points

    operator bool() const {
        return hit;
    }
};

class Raycast {
    private:
        const ObjectFactory& objectFactory;
        Vec3 eye;
    public:
        Raycast() = default;
        Raycast(Vec3 eye, const ObjectFactory& objectFactory);

        Vec3 GetEye();
        void SetEye(Vec3 eye);
        Vec3 CalcRayDirAtPoint(Vec3 point) const;
        Vec3 CalcRayDirAtPoint(Vec3 point, Vec3 intersectedPoint) const;
        RayHit GetRayHit(Ray ray, Mesh *currentMeshHit);
        Vec3 IsShadow(Light *light, Vec3 eye, Mesh *intersectedShape);
        Color TraceRay(Vec3 point, Color background, pair<Vec3, bool> &intersectedPoint);
        Color ShadeRay(RayHit hit, Color background, int depth, float currentIOR);
};
}
#endif