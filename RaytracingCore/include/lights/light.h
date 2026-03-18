#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "object.h"
#include <cstdint>

enum class LightSourceType {
	LIGHT,
	ATTLIGHT
};

enum class LightType {
	DIRECTIONAL,
	POINT
};

struct LightData {
	Vec3 lightVec;
	float intensity;
};

class Light : public Object
{
	protected:
		Vec3 lightDir;
		static std::map<LightSourceType, string> sourceTypeMap; 
		static std::map<LightType, string> typeMap; 
	public:
		float intensity;
		LightType type; // 0 = direction, 1 = point
		Vec3 consts;

		Light(Vec3 pos, float intensity);
		Light(Vec3 pos, float intensity, string name);
        Light(Vec3 pos, float intensity, LightType type);
        Light(Vec3 pos, float intensity, string name, LightType type);

        static std::map<LightSourceType, string> GetSourceTypeMap();
		static std::map<LightType, string> GetTypeMap();

		void SetAtLightConst(Vec3 consts)  { this->consts = consts; };

		virtual void SetLightDir(Vec3 lightDir) = 0;
		virtual Vec3 GetLightDir(Vec3 surfacePos) const { return lightDir; }
		virtual bool CompareDistToLight(Vec3 initalObject, Vec3 distToObject) { return false; }

		string GetName() override;

		string ToString() const;
		int CheckArgs();
};

#endif