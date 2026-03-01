#include "shapes/shape.h"

map<ShapeType, string> Shape::typeMap = {
    {ShapeType::SPHERE, "sphere"},
    {ShapeType::CYLINDER, "cylinder"},
    {ShapeType::CONE, "cone"},
    {ShapeType::ELLIPSOID, "ellipsoid"}
};

Shape::Shape(Vec3 pos, int mat, ShapeType type) : Object(pos), mat(mat), type(type) {}

float Shape::GetHitDistance(float A, float B, float C)
{
    float discriminant = pow(B, 2) - 4 * A * C;
    if (discriminant < 0) {
        return -1;
    }

    float t = (-B - sqrt(discriminant)) / (2 * A); 
    float t2 = (-B + sqrt(discriminant)) / (2 * A); 
    if (t < 0 && t2 < 0) {
        return -1;
    }
    if (t < 0 && t2 > 0) {
        t = t2;
    }
    if (t2 < t && t2 > 0) {
        t = t2;
    }
    return t;
}

map<ShapeType, string> Shape::GetTypeMap() {
    return typeMap;
}

string Shape::GetName()
{
    return "default shape";
}