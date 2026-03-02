#include "factory/MeshFactory.h"

MeshFactory::MeshFactory() {}

string MeshFactory::GetTypeIndex(int index)
{
    MeshType type = static_cast<MeshType>(index);
    return Mesh::GetTypeMap()[type];
}

int MeshFactory::CreateObject(string &objectName, vector<float> &args)
{
    std::map<MeshType, std::string> type = Mesh::GetTypeMap();
    if (type[MeshType::SPHERE] == objectName) {
        objects.push_back(new Sphere(args));
    } else if (type[MeshType::CYLINDER] == objectName) {
        objects.push_back(new Cylinder(args));
    } else if (type[MeshType::CONE] == objectName) {
        objects.push_back(new Cone(args));
    } else if (type[MeshType::ELLIPSOID] == objectName) {
        objects.push_back(new Ellipsoid(args));
    } else if (type[MeshType::VERTEX] == objectName) {
        vertices.emplace_back(Vec3(args[0],args[1],args[2]));
    } else if (type[MeshType::INDICE] == objectName) {
        objects.push_back(new Triangle({vertices[(int)args[0]-1],vertices[(int)args[1]-1],vertices[(int)args[2]-1]}, args[3]));
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