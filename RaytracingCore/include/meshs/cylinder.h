#ifndef CYLINDER_H
#define CYLINDER_H

#include "mesh.h"

struct CylinderData {
    Vec3 pos;
    Vec3 direction;
    float radius;
    float length;
    int mat;
    int tex;
};

struct Cylinder : public Mesh {
    public:
        float radius;
        float length;
        Vec3 direction;

        Cylinder() = default;
        Cylinder(Vec3 pos, Vec3 direction, float radius, float length, int mat);
        Cylinder(CylinderData data);
        Cylinder(vector<float> &args);

        CylinderData ParseArgs(vector<float> &args);

        bool CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection) override;

        Vec3 GetNormal(Vec3 intersectedPoint) override;
        pair<float, float> GetTexUV(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif