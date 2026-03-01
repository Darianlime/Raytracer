#include "factory/LightFactory.h"

LightFactory::LightFactory() {}

string LightFactory::GetTypeIndex(int index)
{
    LightSourceType type = static_cast<LightSourceType>(index);
    return Light::GetTypeMap()[type];
}

int LightFactory::CreateObject(string& objectName, vector<float>& args)
{
    map<LightSourceType, std::string> type = Light::GetTypeMap();
    if (objectName != type[LightSourceType::LIGHT] && objectName != type[LightSourceType::ATTLIGHT]) { return 0; }
    switch (int(args[3])) {
        case (int)LightType::DIRECTIONAL:
            cout << "created dir light" << endl;
            objects.push_back(new DirectionalLight(args));
            break;
        case (int)LightType::POINT:
            cout << "created point light" << endl;
            objects.push_back(new PointLight(args));
            break;
    }
    return 0;
}
