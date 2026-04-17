#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector.h"
#include "ray.h"
#include <vector>

enum class BufferType {
    VERTEX,
    VERTEXNORMAL,
    VERTEXTEXTURE,
    INDICE
};

enum class ShadeType {
    NONE,
    TEXTURED,
    SMOOTH,
    SMOOTH_TEXTURED
};

struct Vertex {
    Vec3 pos;
    Vec3 normal;
    Vec2 texture;
    Vertex() : pos(0,0,0), normal(0,0,0), texture(0,0) {}
    Vertex(Vec3 pos, Vec3 normal, Vec2 texture) : pos(pos), normal(normal), texture(texture) {}
};

struct Indices  {
    int v1P, v1N, v1T;
    int v2P, v2N, v2T;
    int v3P, v3N, v3T;
    Indices(int v1P, int v1N, int v1T, int v2P, int v2N, int v2T, int v3P, int v3N, int v3T) 
        : v1P(v1P), v1N(v1N), v1T(v1T), v2P(v2P), v2N(v2N), v2T(v2T), v3P(v3P), v3N(v3N), v3T(v3T) {}
};

struct Triangle {
    private:
        Indices indices;
        int mat;
        int tex;
        int shadeType; 
        Vec3 normal;
        Vec2 texture;
    public:
        Triangle() = default;
        Triangle(Indices indices, int mat, int tex);
        Triangle(Indices data);
        Triangle(std::vector<int> &args);

        Indices ParseArgs(std::vector<int> &args);

        bool CheckIntersection(Ray ray, float &entryIntersection, float &exitIntersection, Vec3 &intersection, std::vector<Vec3> &verts);
        Vec3 GetNormal();
        Vec2 GetTexUV();
        Indices GetIndices();
        // void UpdateTransformation() override;
        // string GetName() override;
}; 

#endif