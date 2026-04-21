#ifndef CONE_H
#define CONE_H

#include "model.h"

struct ConeData {
    Vec3 pos;
    Vec3 direction; 
    float angle;
    float height; 
    int mat;
    int tex;
};

struct Cone : public Model {
    public:
        float angle;
        float height;
        Vec3 direction;

        Cone() = default;
        Cone(Vec3 pos, Vec3 direction, float angle, float height, int mat, int tex);
        Cone(ConeData data);
        Cone(vector<float> &args);

        ConeData ParseArgs(vector<float> &args);

        bool CheckIntersection(const Ray& ray, HitRecord& hitRecord) override;

        Vec3 GetNormal(Vec3 intersectedPoint, Vec3 raydir, const int triangleIndex) override;
        Vec2 GetTexUV(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif