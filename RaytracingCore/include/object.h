#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"

class Object {
    protected:
        string name;
    public:
        Vec3 pos;

        Object() = default;
        Object(Vec3 pos);
        Object(Vec3 pos, string name);
        virtual ~Object() {};
        virtual string GetName() { return name; }

}; 

#endif