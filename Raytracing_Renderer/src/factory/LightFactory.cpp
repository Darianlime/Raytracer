#include "factory/LightFactory.h"

LightFactory::LightFactory() {}

int LightFactory::CreateObject(string& objectName, vector<string>& args)
{
    if (objectName != "light") { return 0; }
    switch (stoi(args[4])) {
        case (int)LightType::DIRECTIONAL:
            cout << "created dir light" << endl;
            objects.push_back(new DirectionalLight(Vec3(stof(args[1]), stof(args[2]), stof(args[3])), stof(args[5])));
            break;
        case (int)LightType::POINT:
            cout << "created point light" << endl;
            objects.push_back(new PointLight(Vec3(stof(args[1]), stof(args[2]), stof(args[3])), stof(args[5])));
            break;
    }
    return 0;
}

// Light *LightFactory::CreateLight(LightType objectType, vector<string> args)
// {
//     return nullptr;
// }
