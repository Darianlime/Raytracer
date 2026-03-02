#ifndef SHAPE_H
#define SHAPE_H

#include "object.h"
#include "material.h"
#include "ray.h"

enum class MeshType {
    SPHERE,
    CYLINDER,
    CONE,
    ELLIPSOID,
    TRIANGLE,
    VERTEX,
    INDICE
};

struct Mesh : public Object {
    protected:
        static map<MeshType, string> typeMap;
    public:
        int mat;
        MeshType type;

        Mesh() = default;
        Mesh(int mat, MeshType type);
        Mesh(Vec3 pos, int mat, MeshType type);
        virtual ~Mesh() {};

        virtual pair<Vec3, bool> CheckIntersection(Ray ray) = 0;
        virtual Vec3 GetNormal(Vec3 intersectedPoint) = 0;
        float GetHitDistance(float A, float B, float C);

        static map<MeshType, string> GetTypeMap();
        string GetName() override;
}; 

#endif