#ifndef CYLINDER_H
#define CYLINDER_H

#include "shape.h"

struct CylinderData {
    Vec3 pos;
    Vec3 direction;
    float radius;
    float length;
    int mat;
};

struct Cylinder : public Shape {
    public:
        float radius;
        float length;
        Vec3 direction;

        Cylinder() = default;
        Cylinder(Vec3 pos, Vec3 direction, float radius, float length, int mat);
        Cylinder(CylinderData data);
        Cylinder(vector<float> &args);

        CylinderData ParseArgs(vector<float> &args);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif