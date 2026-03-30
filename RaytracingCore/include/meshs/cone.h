#ifndef CONE_H
#define CONE_H

#include "mesh.h"

struct ConeData {
    Vec3 pos;
    Vec3 direction; 
    float angle;
    float height; 
    int mat;
    int tex;
};

struct Cone : public Mesh {
    public:
        float angle;
        float height;
        Vec3 direction;

        Cone() = default;
        Cone(Vec3 pos, Vec3 direction, float angle, float height, int mat, int tex);
        Cone(ConeData data);
        Cone(vector<float> &args);

        ConeData ParseArgs(vector<float> &args);

        bool CheckIntersection(Ray ray, float& entryIntersection, float& exitIntersection, Vec3& intersection) override; 
        Vec3 GetNormal(Vec3 intersectedPoint) override;
        pair<float, float> GetTexUV(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif