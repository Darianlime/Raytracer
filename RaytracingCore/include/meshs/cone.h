#ifndef CONE_H
#define CONE_H

#include "mesh.h"

struct ConeData {
    Vec3 pos;
    Vec3 direction; 
    float angle;
    float height; 
    int mat;
};

struct Cone : public Mesh {
    public:
        float angle;
        float height;
        Vec3 direction;

        Cone() = default;
        Cone(Vec3 pos, Vec3 direction, float angle, float height, int mat);
        Cone(ConeData data);
        Cone(vector<float> &args);

        ConeData ParseArgs(vector<float> &args);

        pair<Vec3, bool> CheckIntersection(Ray ray) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif