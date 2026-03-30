#include "material.h"

Material::Material() : diffuse(0,0,0,false), specular(0,0,0,false), k(0,0,0), n(0), alpha(0,0,0,false), refractionIndex(1) {}

Material::Material(Color diffuse, Color specular, Vec3 k, float n)
    : diffuse(diffuse), specular(specular), k(k), n(n), alpha(0,0,0,false), refractionIndex(1) {}

Material::Material(Color diffuse, Color specular, Vec3 k, float n, Color alpha, float refractionIndex)
    : diffuse(diffuse), specular(specular), k(k), n(n), alpha(alpha), refractionIndex(refractionIndex) {}

std::string Material::ToString() const {
    return diffuse.ToString() + " " + specular.ToString();
}