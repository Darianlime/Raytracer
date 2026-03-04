#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "mesh.h"

enum class BufferType {
    VERTEX,
    VERTEXNORMAL,
    VERTEXTEXTURE,
    INDICE
};

struct Vertex {
    Vec3 pos;
    Vec3 normal;
    Vec2 texture;
    Vertex() : pos(0,0,0), normal(0,0,0), texture(0,0) {}
    Vertex(Vec3 pos, Vec3 normal, Vec2 texture) : pos(pos), normal(normal), texture(texture) {}
};

struct Indices  {
    Vertex v1;
    Vertex v2;
    Vertex v3;
    Indices(Vertex v1, Vertex v2, Vertex v3) : v1(v1), v2(v2), v3(v3) {}
};

struct Triangle : public Mesh {
    private:
        int mat;
        Indices indices;
    public:
        Triangle() = default;
        Triangle(Indices indices, int mat);
        Triangle(Indices data);
        Triangle(vector<float> &args);

        Indices ParseArgs(vector<float> &args);

        pair<Vec3, bool> CheckIntersection(Ray ray) override;
        Vec3 GetNormal(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif