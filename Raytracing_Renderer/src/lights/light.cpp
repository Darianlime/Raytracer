#include "lights/light.h"

Light::Light(Vec3 pos, int w, float intensity) : Object(pos), w(w), consts(Vec3(1,0,0)), intensity(intensity) {}

Light::Light(Vec3 pos, int w, float intensity, string name) : Object(pos, name), w(w), consts(Vec3(1,0,0)), intensity(intensity) {}

Light::Light(Vec3 pos, int w, float intensity, string name, LightType type) : Object(pos, name), w(w), intensity(intensity), consts(Vec3(1,0,0)), type(type) {}
