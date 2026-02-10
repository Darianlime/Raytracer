#include "objects/cone.h"

Cone::Cone(Vec3 tip, Vec3 direction, float angle, float height, Color mat) 
    : Object(tip, mat, "cone"), angle(angle), direction(direction), height(height) {}

pair<Vec3, bool> Cone::CheckIntersection(Ray ray) {
    
    return pair<Vec3, bool>(Vec3(0,0,0), true);
}