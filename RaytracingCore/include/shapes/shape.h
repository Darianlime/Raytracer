#ifndef SHAPE_H
#define SHAPE_H


#include "object.h"
#include "material.h"
#include "ray.h"

enum class ShapeType {
    SPHERE,
    CYLINDER,
    CONE,
    ELLIPSOID
};

struct Shape : public Object {
    public:
        int mat;

        Shape() = default;
        Shape(Vec3 pos, int mat, string name);
        virtual ~Shape() {};

        virtual pair<Vec3, bool> CheckIntersection(Ray ray) = 0;
        virtual Vec3 GetNormal(Vec3 intersectedPoint) = 0;
        float GetHitDistance(float A, float B, float C); 

}; 

#endif