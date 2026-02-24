#include "lights/PointLight.h"

PointLight::PointLight(Vec3 pos, float intensity) : Light(pos, 1, intensity, "Point Light", LightType::POINT) {}

Vec3 PointLight::GetLightDir(Vec3 surfacePos) const {
    return (pos - surfacePos) / Vec3::Mag(pos - surfacePos);
}

bool PointLight::CompareDistToLight(Vec3 initalObject, Vec3 distToObject)
{
    return Vec3::Dist(initalObject, pos) < Vec3::Dist(initalObject, distToObject);
}
