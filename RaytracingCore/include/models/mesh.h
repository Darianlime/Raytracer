#ifndef MESH_H
#define MESH_H

#include "model.h"

struct Mesh : public Model {
    public:
        std::string name;
        Vec3 currentNormal;
        Vec2 currentTexture;

        Mesh();
        Mesh(std::string name, std::vector<int> args);

        bool CheckIntersection(Ray ray, HitRecord& hitRecord) override;
        void CenterOrgVertsToCenter();
        void UpdateTransformation() override;
        Vec3 GetNormal(Vec3 intersectedPoint, Vec3 raydir) override;
        Vec2 GetTexUV(Vec3 intersectedPoint) override;

        std::string GetName();
}; 

#endif