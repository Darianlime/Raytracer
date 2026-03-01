#include "factory/Shapefactory.h"

ShapeFactory::ShapeFactory() {}

string ShapeFactory::GetTypeIndex(int index)
{
    ShapeType type = static_cast<ShapeType>(index);
    return Shape::GetTypeMap()[type];
}

int ShapeFactory::CreateObject(string &objectName, vector<float> &args)
{
    std::map<ShapeType, std::string> type = Shape::GetTypeMap();
    if (type[ShapeType::SPHERE] == objectName) {
        objects.push_back(new Sphere(args));
    } else if (type[ShapeType::CYLINDER] == objectName) {
        objects.push_back(new Cylinder(args));
    } else if (type[ShapeType::CONE] == objectName) {
        objects.push_back(new Cone(args));
    } else if (type[ShapeType::ELLIPSOID] == objectName) {
        objects.push_back(new Ellipsoid(args));
    }
    // switch (typeMap[objectName]) {
    //     case ShapeType::SPHERE:
    //         if (args.size() < 5) { cerr << "Error: failed to create object sphere not enough args" << endl; return -1; }
    //         objects.push_back(new Sphere(Vec3(stof(args[1]),stof(args[2]),stof(args[3])), stof(args[4]), stoi(args[5])));
    //         break;
    //     case ShapeType::CYLINDER:
    //         if (args.size() < 9) { cerr << "Error: failed to create object cylinder not enough args" << endl; return -1; }
    //         objects.push_back(new Cylinder(Vec3(stof(args[1]),stof(args[2]),stof(args[3])), Vec3(stof(args[4]), stof(args[5]), stof(args[6])), stof(args[7]), stof(args[8]), stoi(args[9])));
    //         break;
    //     case ShapeType::CONE:
    //         if (args.size() < 9) { cerr << "Error: failed to create object cone not enough args" << endl; return -1; }
    //         objects.push_back(new Cone(Vec3(stof(args[1]),stof(args[2]),stof(args[3])), Vec3(stof(args[4]), stof(args[5]), stof(args[6])), stof(args[7]), stof(args[8]), stoi(args[9])));
    //         break;
    //     case ShapeType::ELLIPSOID:
    //         if (args.size() < 7) { cerr << "Error: failed to create object ellipsoid not enough args" << endl; return -1; }
    //         objects.push_back(new Ellipsoid(Vec3(stof(args[1]),stof(args[2]),stof(args[3])), Vec3(stof(args[4]), stof(args[5]), stof(args[6])), stoi(args[7])));
    //         break;
    // }
    return 0;
}