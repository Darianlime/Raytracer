#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <vector>
#include "objects/sphere.h"
#include "objects/cylinder.h"
#include "objects/cone.h"
#include "objects/ellipsoid.h"

class ObjectFactory {
    private:
        vector<Object*> objects;
    public:
        ObjectFactory() = default;
        ~ObjectFactory() {};
        int CreateObject(string objectName, vector<string> args, Material mat);
        Object* CreateObject(ObjectType objectType, vector<string> args, Material mat);

        vector<Object*> GetObjects() const { return objects; }

}; 

#endif