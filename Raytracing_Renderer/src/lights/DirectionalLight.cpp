#include "lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(Vec3 direction, float intensity) : Light(direction, 0, intensity, "Directional Light")
{
    SetLightDir((-direction) / Vec3::Mag(direction)); 
}