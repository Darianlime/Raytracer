#include "factory/LightFactory.h"

LightFactory::LightFactory() {}

string LightFactory::GetTypeIndex(int index)
{
    LightSourceType type = static_cast<LightSourceType>(index);
    return Light::GetTypeMap()[type];
}

int LightFactory::CreateObject(string& objectName, vector<string>& args)
{
    map<LightSourceType, std::string> type = Light::GetTypeMap();
    if (objectName != type[LightSourceType::LIGHT] && objectName != type[LightSourceType::ATTLIGHT]) { return 0; }

    vector<float> lightsArgs(args.size());
    for (int i = 0; i < lightsArgs.size(); i++) {
        lightsArgs[i] = stof(args[i]);
    }
    switch ((int)lightsArgs[3]) {
        case (int)LightType::DIRECTIONAL:
            std::cout << "created dir light" << std::endl;
            objects.push_back(make_unique<DirectionalLight>(lightsArgs));
            break;
        case (int)LightType::POINT:
            std::cout << "created point light" << std::endl;
            objects.push_back(make_unique<PointLight>(lightsArgs));
            break;
    }
    return 0;
}

int LightFactory::GetTypeMapSize()
{
    return Light::GetTypeMap().size();
}
