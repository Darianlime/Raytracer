#include "lights/light.h"

std::map<LightSourceType, string> Light::sourceTypeMap = {
    {LightSourceType::LIGHT,"light"},
    {LightSourceType::ATTLIGHT,"attlight"}
};

std::map<LightType, string> Light::typeMap = {
    {LightType::DIRECTIONAL,"directional"},
    {LightType::POINT,"point"}
};

Light::Light(Vec3 pos, float intensity) : Object(pos), consts(Vec3(1,0,0)), intensity(intensity) {}

Light::Light(Vec3 pos, float intensity, string name) : Object(pos, name), consts(Vec3(1,0,0)), intensity(intensity) {}

Light::Light(Vec3 pos, float intensity, LightType type) : Object(pos), intensity(intensity), consts(Vec3(1,0,0)), type(type) {}

Light::Light(Vec3 pos, float intensity, string name, LightType type) : Object(pos, name), intensity(intensity), consts(Vec3(1,0,0)), type(type) {}

std::map<LightSourceType, string> Light::GetSourceTypeMap()
{
    return sourceTypeMap;
}

std::map<LightType, string> Light::GetTypeMap()
{
    return typeMap;
}

string Light::GetName()
{
    return "Default light";
}
