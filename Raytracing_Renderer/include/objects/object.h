#ifndef OBJECT_H
#define OBJECT_H

#include "../vector.h"
#include "../color.h"
#include "../raycast.h"

struct Object {
    protected:
        string name;
    public:
        Vec3 pos;
        Color mat;

        Object() = default;
        Object(Vec3 pos, Color mat, string name);
        virtual ~Object() {};

        virtual pair<Vec3, bool> CheckIntersection(Raycast ray) = 0; 
        string GetName() { return name; }

}; 

#endif