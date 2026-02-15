#ifndef LIGHT_FACTORY_H
#define LIGHT_FACTORY_H

#include <vector>
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"

class LightFactory {
    private:
        vector<Light*> lights;
    public:
        LightFactory() = default;
        ~LightFactory() {};
        int CreateLight(string objectName, vector<string> args);
        Light* CreateLight(LightType objectType, vector<string> args);

        vector<Light*> GetObjects() const { return lights; }
}; 

#endif