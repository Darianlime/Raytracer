#include "factory/ObjectFactory.h"

ObjectFactory::ObjectFactory() {
    AddMaterial(Material(Color(0,0,0,false), Color(1,1,1,false), Vec3(0.2,0.6,0.2), 10.0f));
}

std::unordered_map<std::type_index, unique_ptr<IFactory>>& ObjectFactory::GetFactoryMap() {
    return factories;
}

void ObjectFactory::AddMaterial(Material mat)
{
    materials.push_back(mat);
}

void ObjectFactory::AddTexture(Texture tex)
{
    textures.push_back(tex);
}

const vector<Material> &ObjectFactory::GetMats()
{
    return materials;
}

const Material& ObjectFactory::GetMatIndex(int index)
{
    return materials[index];
}

Texture& ObjectFactory::GetTexIndex(int index)
{
    return textures[index];
}
