#ifndef MESH_H
#define MESH_H

#include "models/geometry.h"
#include "vector.h"
#include <string>
#include <vector>

struct Mesh {
    public:
        std::string name;
        Vec3 pos;
        Vec3 rotation;
        Vec3 size;
        int startIndice;
        int endIndice;
        std::vector<Vec3> verts;

        Mesh();
        Mesh(std::string name, std::vector<int> args);

        void CalculateCentriod();

        // bool CheckIntersection(Ray ray, float &entryIntersection, float &exitIntersection, Vec3 &intersection) override;
        // Vec3 GetNormal(Vec3 intersectedPoint, Vec3 raydir) override;
        // Vec2 GetTexUV(Vec3 intersectedPoint) override;

        std::string GetName();
}; 

#endif