#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight : public Light
{
	public:
		DirectionalLight(Vec3 direction, float intensity) 
            : Light(direction, 0, intensity)
        {
            SetLightDir((-direction) / Vec3::Mag(direction)); 
        }
};

#endif