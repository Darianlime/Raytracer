#include "lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(Vec3 direction, float intensity) : Light(direction, intensity, LightType::DIRECTIONAL)
{
    SetLightDir((-direction) / Vec3::Mag(direction)); 
}

DirectionalLight::DirectionalLight(LightData data)
    : Light(data.lightVec, data.intensity, LightType::DIRECTIONAL) {}

DirectionalLight::DirectionalLight(vector<float> &args) 
    : DirectionalLight(ParseArgs(args)) {}

LightData DirectionalLight::ParseArgs(vector<float> &args) {
    if (args.size() < 4) {
        return LightData{Vec3(0.0f,0.0f,0.0f), 1.0f};
    }
    return LightData{Vec3(args[0], args[1], args[2]), args[4]};
}

string DirectionalLight::GetName()
{
    return "Directional Light";
}