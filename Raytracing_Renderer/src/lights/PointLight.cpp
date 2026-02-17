#include "lights/PointLight.h"

PointLight::PointLight(Vec3 pos, float intensity) : Light(pos, 1, intensity, "Point Light") {}

Vec3 PointLight::GetLightDir(Vec3 surfacePos) const {
    return (pos - surfacePos) / Vec3::Mag(pos - surfacePos);
}
