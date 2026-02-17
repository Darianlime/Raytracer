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

		Light(Vec3 pos, int w, float intensity);
		Light(Vec3 pos, int w, float intensity, string name);

		void SetLightDir(Vec3 lightDir) { this->lightDir = lightDir; }
		virtual Vec3 GetLightDir(Vec3 surfacePos) const { return lightDir; }

		string ToString() const;
		int CheckArgs();
};

#endif