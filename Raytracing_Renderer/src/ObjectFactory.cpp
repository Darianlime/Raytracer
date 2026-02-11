#include "factory/ObjectFactory.h"

Object *ObjectFactory::CreateObject(string objectName, vector<string> args, Color mat)
{
    if (objectName == "sphere") {
        objects.push_back(new Sphere(Vec3(stof(args[0]),stof(args[1]),stof(args[2])), stof(args[3]), mat));
    } else if (objectName == "cylinder") {
        objects.push_back(new Cylinder(Vec3(stof(args[0]),stof(args[1]),stof(args[2])), Vec3(stof(args[3]), stof(args[4]), stof(args[5])), stof(args[6]), stof(args[7]), mat));
    } else if (objectName == "cone") {
        objects.push_back(new Cone(Vec3(stof(args[0]),stof(args[1]),stof(args[2])), Vec3(stof(args[3]), stof(args[4]), stof(args[5])), stof(args[6]), stof(args[7]), mat));
    } else if (objectName == "ellipsoid") {
        objects.push_back(new Ellipsoid(Vec3(stof(args[0]),stof(args[1]),stof(args[2])), Vec3(stof(args[3]), stof(args[4]), stof(args[5])), mat));
    }
    return nullptr;
}

Object *ObjectFactory::CreateObject(ObjectType objectType, vector<string> args, Color mat)
{
    switch (objectType) {
        case ObjectType::SPHERE:
            objects.push_back(new Sphere(Vec3(stof(args[0]), stof(args[1]),stof(args[2])), stof(args[3]), mat));
            break;
        case ObjectType::CYLINDER:
            objects.push_back(new Cylinder(Vec3(stof(args[0]),stof(args[1]),stof(args[2])), Vec3(stof(args[3]), stof(args[4]), stof(args[5])), stof(args[6]), stof(args[7]), mat));
            break;
        case ObjectType::CONE:
            objects.push_back(new Cone(Vec3(stof(args[0]),stof(args[1]),stof(args[2])), Vec3(stof(args[3]), stof(args[4]), stof(args[5])), stof(args[6]), stof(args[7]), mat));
            break;
    }
    return nullptr;
}