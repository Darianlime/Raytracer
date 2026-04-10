#ifndef SPHERE_H
#define SPHERE_H

#include "model.h"

struct SphereData {
    Vec3 pos;
    float radius;
    int mat;
    int tex;
};

struct Sphere : public Model {
    public:
        float radius;

        Sphere() = default;
        Sphere(Vec3 pos, float radius, int mat);
        Sphere(SphereData data);
        Sphere(vector<float> &args);

        SphereData ParseArgs(vector<float>& args);

        bool CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection) override; 
        Vec3 GetNormal(Vec3 intersectedPoint, Vec3 raydir) override;
        Vec2 GetTexUV(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif