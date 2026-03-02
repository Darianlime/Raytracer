#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "mesh.h"

struct Vertex {
    Vec3 pos;
    Vec3 normal;
    Vertex(Vec3 pos) : pos(pos) {}
    Vertex(Vec3 pos, Vec3 normal) : pos(pos), normal(normal) {}
};

struct Indices  {
    Vertex v1;
    Vertex v2;
    Vertex v3;

    Indices(Vertex v1, Vertex v2, Vertex v3) : v1(v1), v2(v2), v3(v3) {}
};

struct Triangle : public Mesh {
    private:
        Indices indices;
    public:
        Triangle() = default;
        Triangle(Indices indices, int mat);

        //Triangle(SphereData data);
        //Triangle(vector<float> &args);

        //SphereData ParseArgs(vector<float>& args);
        pair<Vec3, bool> CheckIntersection(Ray ray) override;
        Vec3 GetNormal(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif