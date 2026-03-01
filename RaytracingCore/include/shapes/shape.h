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
    protected:
        static map<ShapeType, string> typeMap;
    public:
        int mat;
        ShapeType type;

        Shape() = default;
        Shape(Vec3 pos, int mat, ShapeType type);
        virtual ~Shape() {};

        virtual pair<Vec3, bool> CheckIntersection(Ray ray) = 0;
        virtual Vec3 GetNormal(Vec3 intersectedPoint) = 0;
        float GetHitDistance(float A, float B, float C);

        static map<ShapeType, string> GetTypeMap();
        string GetName() override;
}; 

#endif