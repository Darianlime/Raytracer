#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "model.h"

struct EllipsoidData {
    Vec3 pos;
    Vec3 radius;
    int mat;
    int tex;
};

struct Ellipsoid : public Model {
    public:
        Vec3 radius;

        Ellipsoid() = default;
        Ellipsoid(Vec3 pos, Vec3 radius, int mat);
        Ellipsoid(EllipsoidData data);
        Ellipsoid(vector<float> &args);

        EllipsoidData ParseArgs(vector<float> &args);

        bool CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection) override; 
        Vec3 GetNormal(Vec3 intersectedPoint, Vec3 raydir) override;
        Vec2 GetTexUV(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif