#include "factory/ObjectFactory.h"

ObjectFactory::ObjectFactory() {
    CreateFactory<MeshFactory>();
    CreateFactory<LightFactory>();
}

std::unordered_map<std::type_index, unique_ptr<IFactory>>& ObjectFactory::GetFactoryMap() {
    return factories;
}

void ObjectFactory::AddCamera(Raytracer::Camera camera)
{
    cameras.push_back(camera);
}

const vector<Raytracer::Camera> &ObjectFactory::GetCameras() const
{
    return cameras;
}

Raytracer::Camera &ObjectFactory::GetCameraIndex(int index)
{
    return cameras[index];
}

const int ObjectFactory::GetCameraSize() const
{
    return cameras.size();
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
