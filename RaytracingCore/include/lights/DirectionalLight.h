#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "light.h"

class DirectionalLight : public Light
{
	public:
        DirectionalLight();
		DirectionalLight(Vec3 direction, float intensity);
        DirectionalLight(LightData data);
        DirectionalLight(vector<float> &args);
        LightData ParseArgs(vector<float> &args);

        void SetLightDir(Vec3 lightDir) override;

		string GetName() override;
};

#endif