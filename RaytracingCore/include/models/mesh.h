#ifndef MESH_H
#define MESH_H

#include "model.h"

struct Mesh : public Model {
    private:
        string name;
        Vec3 currentNormal;
        Vec2 currentTexture;
    public:
        Mesh();
        Mesh(string name, vector<int> args);

        bool CheckIntersection(Ray ray, float &entryIntersection, float &exitIntersection, Vec3 &intersection) override;
        Vec3 GetNormal(Vec3 intersectedPoint, Vec3 raydir) override;
        Vec2 GetTexUV(Vec3 intersectedPoint) override;

        string GetName() override;
}; 

#endif