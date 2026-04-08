#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include "matrix.h"
#include <vector>
#include <string>
#include <map>

using std::string;
using std::vector;
using std::map;

class Object {
    protected:
        string name;
    public:
        Vec3 pos;
        Vec3 rot;
        Vec3 size;

        Matrix4 localToWorld;
        Matrix4 worldToLocal;

        Object() = default;
        Object(Vec3 pos);
        Object(Vec3 pos, Vec3 rot, Vec3 size);
        Object(Vec3 pos, string name);
        Object(Vec3 pos, Vec3 rot, Vec3 size, string name);

        void SetMatrix(Vec3 pos, Vec3 rot, Vec3 size);
        void UpdateRotation();

        virtual ~Object() {};
        virtual string GetName() { return name; }

}; 

#endif