#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include <cstdint>
#include <string>

using namespace std;

struct Material {
    Color diffuse;
    Color specular;
    Vec3 k; // scalar values 
    float n;

	Material();
	Material(Color diffuse, Color specular, Vec3 k, float n);

	string ToString() const;
	//int CheckArgs();
};

#endif