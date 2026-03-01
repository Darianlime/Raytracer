#include "lights/light.h"

map<LightSourceType, string> Light::typeMap = {
    {LightSourceType::LIGHT,"light"},
    {LightSourceType::ATTLIGHT,"attlight"}
};

Light::Light(Vec3 pos, float intensity) : Object(pos), consts(Vec3(1,0,0)), intensity(intensity) {}

Light::Light(Vec3 pos, float intensity, string name) : Object(pos, name), consts(Vec3(1,0,0)), intensity(intensity) {}

Light::Light(Vec3 pos, float intensity, LightType type) : Object(pos), intensity(intensity), consts(Vec3(1,0,0)), type(type) {}

Light::Light(Vec3 pos, float intensity, string name, LightType type) : Object(pos, name), intensity(intensity), consts(Vec3(1,0,0)), type(type) {}

map<LightSourceType, string> Light::GetTypeMap()
{
    return typeMap;
}

string Light::GetName()
{
    return "Default light";
}
