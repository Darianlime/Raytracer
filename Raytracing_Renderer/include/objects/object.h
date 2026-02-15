#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include "material.h"
#include "ray.h"

enum class ObjectType {
    SPHERE,
    CYLINDER,
    CONE,
    ELLIPSOID
};

struct Object {
    protected:
        string name;
    public:
        Vec3 pos;
        Material mat;

        Object() = default;
        Object(Vec3 pos, Material mat, string name);
        virtual ~Object() {};

        virtual pair<Vec3, bool> CheckIntersection(Ray ray) = 0;
        virtual Vec3 GetNormal(Vec3 intersectedPoint) = 0;
        float GetHitDistance(float A, float B, float C); 
        string GetName() { return name; }

}; 

#endif