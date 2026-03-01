#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight : public Light
{
	public:
		DirectionalLight(Vec3 direction, float intensity);
        DirectionalLight(LightData data);
        DirectionalLight(vector<float> &args);
        LightData ParseArgs(vector<float> &args);

		string GetName() override;
};

#endif