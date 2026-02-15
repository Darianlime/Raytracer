#include "factory/ObjectFactory.h"

int ObjectFactory::CreateObject(string objectName, vector<string> args, Material mat)
{
    if (objectName == "sphere") {
        if (args.size() < 5) { cerr << "Error: failed to create object sphere not enough args" << endl; return -1; }
        objects.push_back(new Sphere(Vec3(stof(args[1]),stof(args[2]),stof(args[3])), stof(args[4]), mat));
    } else if (objectName == "cylinder") {
        if (args.size() < 9) { cerr << "Error: failed to create object cylinder not enough args" << endl; return -1; }
        objects.push_back(new Cylinder(Vec3(stof(args[1]),stof(args[2]),stof(args[3])), Vec3(stof(args[4]), stof(args[5]), stof(args[6])), stof(args[7]), stof(args[8]), mat));
    } else if (objectName == "cone") {
        if (args.size() < 9) { cerr << "Error: failed to create object cone not enough args" << endl; return -1; }
        objects.push_back(new Cone(Vec3(stof(args[1]),stof(args[2]),stof(args[3])), Vec3(stof(args[4]), stof(args[5]), stof(args[6])), stof(args[7]), stof(args[8]), mat));
    } else if (objectName == "ellipsoid") {
        if (args.size() < 7) { cerr << "Error: failed to create object ellipsoid not enough args" << endl; return -1; }
        objects.push_back(new Ellipsoid(Vec3(stof(args[1]),stof(args[2]),stof(args[3])), Vec3(stof(args[4]), stof(args[5]), stof(args[6])), mat));
    }
    return 0;
}

Object *ObjectFactory::CreateObject(ObjectType objectType, vector<string> args, Material mat)
{
    // switch (objectType) {
    //     case ObjectType::SPHERE:
    //         objects.push_back(new Sphere(Vec3(stof(args[0]), stof(args[1]),stof(args[2])), stof(args[3]), mat));
    //         break;
    //     case ObjectType::CYLINDER:
    //         objects.push_back(new Cylinder(Vec3(stof(args[0]),stof(args[1]),stof(args[2])), Vec3(stof(args[3]), stof(args[4]), stof(args[5])), stof(args[6]), stof(args[7]), mat));
    //         break;
    //     case ObjectType::CONE:
    //         objects.push_back(new Cone(Vec3(stof(args[0]),stof(args[1]),stof(args[2])), Vec3(stof(args[3]), stof(args[4]), stof(args[5])), stof(args[6]), stof(args[7]), mat));
    //         break;
    // }
    return nullptr;
}