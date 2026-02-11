#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <vector>
#include "objects/sphere.h"
#include "objects/cylinder.h"
#include "objects/cone.h"

enum class ObjectType {
    SPHERE,
    CYLINDER,
    CONE
};

class ObjectFactory {
    private:
        vector<Object*> objects;
    public:
        ObjectFactory() = default;
        ~ObjectFactory() {}
        Object* CreateObject(string objectName, vector<string> args, Color mat);
        Object* CreateObject(ObjectType objectType, vector<string> args, Color mat);

        vector<Object*> GetObjects() const { return objects; }

}; 

#endif