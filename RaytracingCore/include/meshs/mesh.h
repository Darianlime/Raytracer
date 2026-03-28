#ifndef SHAPE_H
#define SHAPE_H

#include "object.h"
#include "material.h"
#include "ray.h"

using std::pair;

enum class MeshType {
    SPHERE,
    CYLINDER,
    CONE,
    ELLIPSOID,
    TRIANGLE
};

struct Mesh : public Object {
    protected:
        static map<MeshType, string> typeMap;
    public:
        int mat;
        int tex;
        MeshType type;

        Mesh() = default;
        Mesh(int mat, int tex, MeshType type);
        Mesh(Vec3 pos, int mat, int tex, MeshType type);
        Mesh(Vec3 pos, Vec3 rot, Vec3 size, int mat, int tex, MeshType type);
        virtual ~Mesh() {};

        virtual pair<Vec3, bool> CheckIntersection(Ray ray) = 0;
        virtual Vec3 GetNormal(Vec3 intersectedPoint) = 0;
        virtual pair<float, float> GetTexUV(Vec3 intersectedPoint) = 0;
        float GetHitDistance(float A, float B, float C);

        static map<MeshType, string>& GetTypeMap();
        string GetName() override;
}; 

#endif