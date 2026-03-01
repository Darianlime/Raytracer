#include "lights/PointLight.h"

PointLight::PointLight(Vec3 pos, float intensity) : Light(pos, intensity, LightType::POINT) {}

PointLight::PointLight(LightData data)
    : Light(data.lightVec, data.intensity, LightType::POINT) {}

PointLight::PointLight(vector<float> &args) 
    : PointLight(ParseArgs(args)) {}

LightData PointLight::ParseArgs(vector<float> &args) {
    if (args.size() < 4) {
        return LightData{Vec3(0.0f,0.0f,0.0f), 1.0f};
    }
    if (args.size() >= 7) {
        Vec3 consts(args[5], args[6], args[7]);
        if (consts == Vec3::Zero()) {
            consts = Vec3(1,0,0);
        }
        SetAtLightConst(consts);
        cout << "set att light point light" << endl;
    }
    return LightData{Vec3(args[0], args[1], args[2]), args[4]};
}

Vec3 PointLight::GetLightDir(Vec3 surfacePos) const {
    return (pos - surfacePos) / Vec3::Mag(pos - surfacePos);
}

bool PointLight::CompareDistToLight(Vec3 initalObject, Vec3 distToObject)
{
    return Vec3::Dist(initalObject, pos) < Vec3::Dist(initalObject, distToObject);
}

string PointLight::GetName()
{
    return "Directional Light";
}