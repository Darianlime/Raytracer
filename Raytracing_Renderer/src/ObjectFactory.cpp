#include "factory/ObjectFactory.h"

Object *ObjectFactory::CreateObject(string objectName, vector<string> args, Color mat)
{
    if (objectName == "sphere") {
        objects.push_back(new Sphere(Vec3(stof(args[0]),stof(args[1]),stof(args[2])), stof(args[3]), mat));
    } else if (objectName == "cylinder") {

    }
    return nullptr;
}