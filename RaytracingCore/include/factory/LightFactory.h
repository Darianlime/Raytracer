#ifndef LIGHT_FACTORY_H
#define LIGHT_FACTORY_H

#include <vector>
#include "factory/FactoryBase.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"

// Creates light objects in the scene
class LightFactory : public FactoryBase<Light> {
    public:
        LightFactory();
        ~LightFactory() {};
        int CreateObject(string& objectName, vector<float>& args) override;
        string GetTypeIndex(int index) override;

        string GetName() override {
            return "Light Factory";
        };
}; 

#endif