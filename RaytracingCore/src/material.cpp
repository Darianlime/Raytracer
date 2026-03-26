#include "material.h"

Material::Material() : diffuse(0,0,0,false), specular(0,0,0,false), k(0,0,0), n(0), opacity(1), refractionIndex(1) {}

Material::Material(Color diffuse, Color specular, Vec3 k, float n)
    : diffuse(diffuse), specular(specular), k(k), n(n), opacity(1), refractionIndex(1) {}

Material::Material(Color diffuse, Color specular, Vec3 k, float n, float opacity, float refractionIndex)
    : diffuse(diffuse), specular(specular), k(k), n(n), opacity(opacity), refractionIndex(refractionIndex) {}

std::string Material::ToString() const {
    return diffuse.ToString() + " " + specular.ToString();
}