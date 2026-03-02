#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

struct SphereData {
    Vec3 pos;
    float radius;
    int mat;
};

struct Sphere : public Mesh {
    public:
        float radius;

        Sphere() = default;
        Sphere(Vec3 pos, float radius, int mat);
        Sphere(SphereData data);
        Sphere(vector<float> &args);

        SphereData ParseArgs(vector<float>& args);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif