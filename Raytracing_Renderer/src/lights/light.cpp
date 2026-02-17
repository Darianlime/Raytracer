#include "lights/light.h"

Light::Light(Vec3 pos, int w, float intensity) : Object(pos), w(w), intensity(intensity) {}

Light::Light(Vec3 pos, int w, float intensity, string name) : Object(pos, name), w(w), intensity(intensity) {}