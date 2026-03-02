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
        vector<Vertex> vertices;
    public:
        MeshFactory();
        ~MeshFactory() {};

        int CreateObject(string& objectName, vector<float>& args) override;
        string GetTypeIndex(int index) override;

        string GetName() override {
            return "Mesh Factory";
        };
};

#endif