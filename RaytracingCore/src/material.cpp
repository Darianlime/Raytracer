#include "material.h"

Material::Material() : diffuse(0,0,0,false), specular(0,0,0,false), k(0,0,0), n(0), alpha(0,0,0,false), refractionIndex(1) {}

Material::Material(Color diffuse, Color specular, Vec3 k, float n)
    : diffuse(diffuse), specular(specular), k(k), n(n), alpha(0,0,0,false), refractionIndex(1) {}

Material::Material(Color diffuse, Color specular, Vec3 k, float n, float alpha, float refractionIndex)
    : diffuse(diffuse), specular(specular), k(k), n(n), alpha(alpha,alpha,alpha,false), refractionIndex(refractionIndex) {}

Material::Material(Color diffuse, Color specular, Vec3 k, float n, Color alpha, float refractionIndex)
    : diffuse(diffuse), specular(specular), k(k), n(n), alpha(alpha), refractionIndex(refractionIndex) {}

Material::Material(std::vector<float> &args)
{
    if (args.size() >= 14) {
        diffuse = Color(args[0], args[1], args[2], false);
        specular = Color(args[3], args[4], args[5], false);
        k = Vec3(args[6], args[7], args[8]);
        n = args[9];
        alpha = Color(args[10], args[11], args[12], false);
        refractionIndex = args[13];
    } else {
        diffuse = Color(args[0], args[1], args[2], false);
        specular = Color(args[3], args[4], args[5], false);
        k = Vec3(args[6], args[7], args[8]);
        n = args[9];
        alpha = Color(args[10], args[10], args[10], false);
        refractionIndex = args[11];
    }
}

std::string Material::ToString() const {
    return diffuse.ToString() + " " + specular.ToString();
}