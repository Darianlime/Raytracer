#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

class PointLight : public Light
{
	public:
		PointLight(Vec3 pos, float intensity);

        Vec3 GetLightDir(Vec3 surfacePos) const override;
};

#endif