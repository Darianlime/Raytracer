#ifndef LIGHT_FACTORY_H
#define LIGHT_FACTORY_H

#include <vector>
#include "factory/FactoryBase.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"

// Creates light objects in the scene
class LightFactory : public FactoryBase<Light> {
    private:
        map<string, std::function<unique_ptr<Light>(vector<float>&)>> lightMap;   
    public:
        LightFactory();
        ~LightFactory() {};
        int CreateObject(string& objectName, vector<string>& args) override;
        int GetTypeMapSize() override;
        string GetTypeIndex(int index) override;

        map<string, std::function<unique_ptr<Light>(vector<float>&)>>& GetLightMap();

        string GetName() override {
            return "Light Factory";
        };
}; 

#endif