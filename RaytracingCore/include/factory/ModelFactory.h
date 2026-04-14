#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include <vector>
#include "factory/FactoryBase.h"
#include "models/sphere.h"
#include "models/cylinder.h"
#include "models/cone.h"
#include "models/ellipsoid.h"
#include "models/geometry.h"
#include "models/mesh.h"

class ModelFactory : public FactoryBase<Model> { 
    private:
        map<string, std::function<unique_ptr<Model>(vector<float>&)>> modelMap;
        map<string, std::function<void(vector<float>&)>> geometryMap;
        vector<Vec3> vertsPos;
        vector<Vec3> vertsNormal;
        vector<Vec2> vertsTex;
        vector<Triangle> indices;
        vector<Mesh> meshs;
        int currentVertexStart;
        bool notResetingVertCount;
    public:
        ModelFactory();
        ~ModelFactory() {};

        int CreateObject(string& objectName, vector<string>& args) override;
        void RemoveModel(int index);
        string GetTypeIndex(int index) override;
        int GetTypeMapSize() override;

        void ParseTriangle(vector<string> &args, vector<float> &vertsArgs);
        map<string, std::function<unique_ptr<Model>(vector<float>&)>>& GetModelMap();
        map<string, std::function<void(vector<float>&)>>& GetGeometryMap();
        void AddVertPos(vector<float> &args);
        void AddVertNormal(vector<float> &args);
        void AddVertTex(vector<float> &args);
        void AddIndice(vector<float> &args);
        void AddMesh(string name, vector<int> modelArgs);
        const vector<Mesh>& GetMeshs() const;
        Mesh& GetMeshAtIndex(int index);
        const vector<Vec3>& GetVertsPosition() const;
        void ResetCurrentVertexStart();

        string GetName() override
        {
            return "Mesh Factory";
        };
};

#endif