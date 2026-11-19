#include "factory/ObjectFactory.h"
#include <file.h>

ObjectFactory::ObjectFactory() {
    CreateFactory<ModelFactory>();
    CreateFactory<LightFactory>();
    AddMaterial(Material(Color(1.0f,0.75f,0.79f,false), Color(1,1,1,false), Vec3(0.2,0.6,0.0), 10.0f, Color(1.0f,1.0f,1.0f,false), 1.0f));
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

void ObjectFactory::RemoveMaterial(int index)
{
    materials.erase(materials.begin() + index + 1);
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

void ObjectFactory::CreateObj(const std::string& objPath) {
    GetFactory<ModelFactory>().ResetCurrentVertexStart();
    int intialSize = GetFactory<ModelFactory>().GetObjects().size();
    if (File::ReadOBJ(objPath, -1, -1, *this) == -1) {
        throw std::runtime_error("Failed to read OBJ file");
    }
    int updatedSize = GetFactory<ModelFactory>().GetObjects().size();
    for (int i = intialSize; i < updatedSize; i++) {
        Model* model = GetFactory<ModelFactory>().GetObjects()[i].get();

        Vec3 centroid = model->CalculateCentriod();
        model->pos = centroid;
        for (auto& vertex : model->GetVertices())
        {
            vertex.pos = vertex.pos - centroid;
        }
        for (auto& tri : model->GetTriangles())
        {
            tri.CacheCalculations();
        }

        std::cout << "model pos: " << model->pos.x << ", " << model->pos.y << ", " << model->pos.z << std::endl;
        model->rot.ToString();
        model->SetMatrix(model->pos, model->rot, model->size);
        model->GetBVH().Init();
        model->GetBVH().Build();
        model->localToWorld.ToString();
        std::cout << "model triangles: " << model->GetTriangles().size() << std::endl;
    }
}