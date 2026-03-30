#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

struct SphereData {
    Vec3 pos;
    float radius;
    int mat;
    int tex;
};

struct Sphere : public Mesh {
    public:
        float radius;

        Sphere() = default;
        Sphere(Vec3 pos, float radius, int mat);
        Sphere(SphereData data);
        Sphere(vector<float> &args);

        SphereData ParseArgs(vector<float>& args);

        bool CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;
        pair<float, float> GetTexUV(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif