#include "factory/LightFactory.h"

LightFactory::LightFactory() {
    lightMap["directional"] = [](vector<float>& args) { return make_unique<DirectionalLight>(args); };
    lightMap["point"] = [](vector<float>& args) { return make_unique<PointLight>(args); };
}

string LightFactory::GetTypeIndex(int index)
{
    LightType type = static_cast<LightType>(index);
    return Light::GetTypeMap()[type];
}

int LightFactory::CreateObject(string& objectName, vector<string>& args)
{
    if (lightMap.find(objectName) != lightMap.end()) {
        vector<float> lights;
        objects.push_back(lightMap[objectName](lights));
        return 0;
    }

    if (objectName != "light" && objectName != "attlight") { return 0; }

    args.pop_back();
    args.pop_back();
    std::cout << "light size " << args.size() << std::endl;

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
    return Light::GetSourceTypeMap().size();
}
