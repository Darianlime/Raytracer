#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include <cstdint>
#include <string>
#include <vector>

struct Material {
    Color diffuse;
    Color specular;
    Vec3 k; // scalar values 
    float n;
    Color alpha;
    float refractionIndex;

	Material();
	Material(Color diffuse, Color specular, Vec3 k, float n);
    Material(Color diffuse, Color specular, Vec3 k, float n, float alpha, float refractionIndex);
    Material(Color diffuse, Color specular, Vec3 k, float n, Color alpha, float refractionIndex);

    Material(std::vector<float> &args);

	std::string ToString() const;
	//int CheckArgs();
};

#endif