#ifndef LIGHT_FACTORY_H
#define LIGHT_FACTORY_H

#include <vector>
#include "factory/FactoryBase.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"

class LightFactory : public FactoryBase<Light> {
    public:
        LightFactory();
        ~LightFactory() {};
        int CreateObject(string& objectName, vector<string>& args) override;
        //Light* CreateLight(LightType objectType, vector<string> args);
}; 

#endif