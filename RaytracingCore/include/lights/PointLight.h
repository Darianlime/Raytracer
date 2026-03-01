#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

class PointLight : public Light
{
	public:
		PointLight(Vec3 pos, float intensity);
        PointLight(LightData data);
        PointLight(vector<float> &args);
        LightData ParseArgs(vector<float> &args);

        Vec3 GetLightDir(Vec3 surfacePos) const override;
		bool CompareDistToLight(Vec3 initalObject, Vec3 distToObject) override;

		string GetName() override;
};

#endif