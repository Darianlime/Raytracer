#ifndef CYLINDER_H
#define CYLINDER_H

#include "model.h"

struct CylinderData {
    Vec3 pos;
    Vec3 direction;
    float radius;
    float length;
    int mat;
    int tex;
};

struct Cylinder : public Model {
    public:
        float radius;
        float length;
        Vec3 direction;

        Cylinder() = default;
        Cylinder(Vec3 pos, Vec3 direction, float radius, float length, int mat);
        Cylinder(CylinderData data);
        Cylinder(vector<float> &args);

        CylinderData ParseArgs(vector<float> &args);

        bool CheckIntersection(const Ray& ray, HitRecord& hitRecord) override;

        Vec3 GetNormal(Vec3 intersectedPoint, Vec3 raydir, const int triangleIndex) override;
        Vec2 GetTexUV(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif