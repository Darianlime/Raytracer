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

const vector<Material> &ObjectFactory::GetMats() const
{
    return materials;
}

const int ObjectFactory::GetMatsSize() const
{
    return materials.size();
}

Material &ObjectFactory::GetMatIndex(int index)
{
    return materials[index];
}

const Material& ObjectFactory::GetMatIndex(int index) const
{
    return materials[index];
}

Texture& ObjectFactory::GetTexIndex(int index)
{
    return textures[index];
}

const int ObjectFactory::GetTexSize() const
{
    return textures.size();
}
