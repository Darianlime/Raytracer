#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector.h"
#include "ray.h"
#include <vector>
#include <array>

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

// struct Indices  {
//     int v1P, v1N, v1T;
//     int v2P, v2N, v2T;
//     int v3P, v3N, v3T;
//     Indices(int v1P, int v1N, int v1T, int v2P, int v2N, int v2T, int v3P, int v3N, int v3T) 
//         : v1P(v1P), v1N(v1N), v1T(v1T), v2P(v2P), v2N(v2N), v2T(v2T), v3P(v3P), v3N(v3N), v3T(v3T) {}
// };

struct Indices  {
    Vertex* v1;
    Vertex* v2;
    Vertex* v3;

    // Vertex& GetVertex(int index) { 
    //     if (index == 0) {
    //         return v1;
    //     } else if (index == 1) {
    //         return v2;
    //     } else if (index == 2) {
    //         return v3;
    //     } else {
    //         throw std::runtime_error("Runtime Error: Get indices out of index");
    //     } 
    // }
};

struct Triangle {
    private:
        Indices indices;

        Vec3 v0;
        Vec3 e1;
        Vec3 e2;
        Vec3 cachedNormal;

        int mat;
        int tex;
        int shadeType; 
    public:
        Triangle() = default;
        Triangle(Indices indices, int mat, int tex);
        Triangle(Indices data);
        Triangle(std::vector<int> &args);

        Indices ParseArgs(std::vector<int> &args);

        bool CheckIntersection(const Ray& ray, Vec3& baycentric, float &entryIntersection, float &exitIntersection, Vec3 &intersection);
        Vec3 CalcCenter();
        Vec3 GetNormal(const Vec3 &viewDir);
        Vec2 GetTexUV();
        Indices& GetIndices();
        void SetVertex(Vertex* vertex, int index);
        void CacheCalculations();
        
        // void UpdateTransformation() override;
        // string GetName() override;
}; 

#endif