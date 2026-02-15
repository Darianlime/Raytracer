#include "material.h"

Material::Material() : diffuse(0,0,0,false), specular(0,0,0,false), k(0,0,0), n(0) {}

Material::Material(Color diffuse, Color specular, Vec3 k, float n)
    : diffuse(diffuse), specular(specular), k(k), n(n) {}
