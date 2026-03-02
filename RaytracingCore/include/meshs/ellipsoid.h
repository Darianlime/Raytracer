#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "mesh.h"

struct EllipsoidData {
    Vec3 pos;
    Vec3 radius;
    int mat;
};

struct Ellipsoid : public Mesh {
    public:
        Vec3 radius;

        Ellipsoid() = default;
        Ellipsoid(Vec3 pos, Vec3 radius, int mat);
        Ellipsoid(EllipsoidData data);
        Ellipsoid(vector<float> &args);

        EllipsoidData ParseArgs(vector<float> &args);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif