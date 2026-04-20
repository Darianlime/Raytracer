#ifndef MODEL_H
#define MODEL_H

#include "object.h"
#include "material.h"
#include "ray.h"
#include "BVH/BVH.h"

using std::pair;

enum class ModelType {
    SPHERE,
    CYLINDER,
    CONE,
    ELLIPSOID,
    MESH
};

struct Model : public Object {
    protected:
        static map<ModelType, string> typeMap;
        std::vector<Vec3> orignalVerts;
        BVH bvh;
    public:
        int mat;
        int tex;
        int lastVertIndex;
        int lastIndiceIndex;
        ModelType type;

        Model() = default;
        Model(int mat, int tex, ModelType type);
        Model(Vec3 pos, int mat, int tex, ModelType type);
        Model(Vec3 pos, Vec3 rot, Vec3 size, int mat, int tex, ModelType type);
        virtual ~Model() {};

        virtual bool CheckIntersection(Ray ray, HitRecord& hitRecord) = 0;
        virtual Vec3 GetNormal(Vec3 intersectedPoint, Vec3 raydir) = 0;
        virtual Vec2 GetTexUV(Vec3 intersectedPoint) = 0;

        void CalculateCentriod();
        std::vector<Vec3>& GetVertices();
        std::vector<Vec3> &GetOrgVertices();
        std::vector<Triangle> &GetTriangles();
        BVH &GetBVH();
        pair<float, float> GetHitDistance(float A, float B, float C);
        static map<ModelType, string>& GetTypeMap();
        string GetName() override;
}; 

#endif