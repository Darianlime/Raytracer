#include "factory/ObjectFactory.h"

ObjectFactory::ObjectFactory() {
    CreateFactory<MeshFactory>();
    CreateFactory<LightFactory>();
    AddMaterial(Material(Color(1.0f,0.75f,0.79f,false), Color(1,1,1,false), Vec3(0.2,0.6,0.2), 10.0f, 1.0f, 1.0f));
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
    if (index > -1 && index + 1 < GetMatsSize() && GetMatsSize() > 1) {
        return materials[index+1];
    }
    return materials[0];
}

const Material& ObjectFactory::GetMatIndex(int index) const
{
    if (index > -1 && index + 1 < GetMatsSize() && GetMatsSize() > 1) {
        return materials[index+1];
    }
    return materials[0];
}

const Texture& ObjectFactory::GetTexIndex(int index) const
{
    return textures[index];
}

const int ObjectFactory::GetTexSize() const
{
    return textures.size();
}
