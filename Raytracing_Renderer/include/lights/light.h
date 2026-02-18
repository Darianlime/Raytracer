#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "object.h"
#include <cstdint>
#include <string>

using namespace std;

enum class LightType {
	DIRECTIONAL,
	POINT
};

class Light : public Object
{
	private:
		int w; // 0 = direction, 1 = point
		Vec3 lightDir;
	public:
		float intensity;
		LightType type;

		Light(Vec3 pos, int w, float intensity);
		Light(Vec3 pos, int w, float intensity, string name);
		Light(Vec3 pos, int w, float intensity, string name, LightType type);

		void SetLightDir(Vec3 lightDir) { this->lightDir = lightDir; }
		virtual Vec3 GetLightDir(Vec3 surfacePos) const { return lightDir; }
		virtual bool CompareDistToLight(Vec3 initalObject, Vec3 distToObject) { return false; }

		string ToString() const;
		int CheckArgs();
};

#endif