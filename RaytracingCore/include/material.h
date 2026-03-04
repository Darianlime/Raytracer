#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include <cstdint>
#include <string>

struct Material {
    Color diffuse;
    Color specular;
    Vec3 k; // scalar values 
    float n;

	Material();
	Material(Color diffuse, Color specular, Vec3 k, float n);

	std::string ToString() const;
	//int CheckArgs();
};

#endif