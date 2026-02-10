#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <vector>
#include "objects/sphere.h"
#include "objects/cylinder.h"

class ObjectFactory {
    private:
        vector<Object*> objects;
    public:
        ObjectFactory() = default;
        ~ObjectFactory() {}
        Object* CreateObject(string objectName, vector<string> args, Color mat);

        vector<Object*> GetObjects() const { return objects; }

}; 

#endif