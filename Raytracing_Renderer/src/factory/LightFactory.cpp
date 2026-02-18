#include "factory/LightFactory.h"

LightFactory::LightFactory() {}

int LightFactory::CreateObject(string& objectName, vector<string>& args)
{
    if (objectName != "light" && objectName != "attlight") { return 0; }
    switch (stoi(args[4])) {
        case (int)LightType::DIRECTIONAL:
            cout << "created dir light" << endl;
            objects.push_back(new DirectionalLight(Vec3(stof(args[1]), stof(args[2]), stof(args[3])), stof(args[5])));
            break;
        case (int)LightType::POINT:
            cout << "created point light" << endl;
            objects.push_back(new PointLight(Vec3(stof(args[1]), stof(args[2]), stof(args[3])), stof(args[5])));
            if (objectName == "attlight") {
                Vec3 consts(stof(args[6]), stof(args[7]), stof(args[8]));
                if (consts == Vec3::Zero()) {
                    consts = Vec3(1,0,0);
                }
                objects[objects.size() - 1]->SetAtLightConst(consts);
                cout << "set att light point light" << endl;
            }
            break;
    }
    return 0;
}

// Light *LightFactory::CreateLight(LightType objectType, vector<string> args)
// {
//     return nullptr;
// }
