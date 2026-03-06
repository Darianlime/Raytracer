#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include <vector>
#include "factory/FactoryBase.h"
#include "meshs/sphere.h"
#include "meshs/cylinder.h"
#include "meshs/cone.h"
#include "meshs/ellipsoid.h"
#include "meshs/geometry.h"

class MeshFactory : public FactoryBase<Mesh> { 
    private:
        map<string, std::function<unique_ptr<Mesh>(vector<float>&)>> meshMap;
        map<string, std::function<void(vector<float>&)>> geometryMap;
        vector<Vec3> vertsPos;
        vector<Vec3> vertsNormal;
        vector<Vec2> vertsTex;
    public:
        MeshFactory();
        ~MeshFactory() {};

        int CreateObject(string& objectName, vector<string>& args) override;
        string GetTypeIndex(int index) override;
        int GetTypeMapSize() override;

        void ParseTriangle(vector<string> &args, vector<float> &vertsArgs);
        map<string, std::function<unique_ptr<Mesh>(vector<float>&)>>& GetMeshMap();
        map<string, std::function<void(vector<float>&)>>& GetGeometryMap();
        void AddVertPos(vector<float> &args);
        void AddVertNormal(vector<float> &args);
        void AddVertTex(vector<float> &args);
        void AddTriangle(vector<float> &args);

        string GetName() override
        {
            return "Mesh Factory";
        };
};

#endif