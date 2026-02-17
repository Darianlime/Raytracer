#include "factory/ObjectFactory.h"

ObjectFactory::ObjectFactory() {}

unordered_map<type_index, unique_ptr<IFactory>>& ObjectFactory::GetFactoryMap() {
    return factories;
}

void ObjectFactory::AddMaterial(Material mat)
{
    materials.push_back(mat);
}

const vector<Material>& ObjectFactory::GetMats()
{
    return materials;
}
