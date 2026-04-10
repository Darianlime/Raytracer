#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "factory/LightFactory.h"
#include "factory/ModelFactory.h"
#include "material.h"
#include "texture.h"
#include "camera.h"

// Factory to create new object factories
class ObjectFactory {
    private:
        std::unordered_map<std::type_index, unique_ptr<IFactory>> factories;
        
        vector<Raytracer::Camera> cameras;
        vector<Material> materials;
        vector<Texture> textures;
    public:
        ObjectFactory();
        ~ObjectFactory() {};

        // Creates a factory based on class name as identifier
        template <typename T> 
        void CreateFactory() {
            factories[typeid(T)] = make_unique<T>();
        }

        // Gets Factory based on class name
        template <typename T> 
        T& GetFactory() const {
            auto it = factories.find(typeid(T));
            if (it == factories.end()) {
                throw std::runtime_error("Factory not registered");
            }

            T* factory = dynamic_cast<T*>(it->second.get());

            if (!factory) {
                throw std::logic_error("Factory type mismatch");
            }

            return *factory;
        }

        std::unordered_map<std::type_index, unique_ptr<IFactory>>& GetFactoryMap();

        void AddCamera(Raytracer::Camera camera);
        const vector<Raytracer::Camera> &GetCameras() const;
        Raytracer::Camera& GetCameraIndex(int index);
        const int GetCameraSize() const;

        void AddMaterial(Material mat);
        void RemoveMaterial(int index);
        const vector<Material> &GetMats() const;
        const int GetMatsSize() const;
        Material& GetMatIndex(int index);
        const Material& GetMatIndex(int index) const;

        void AddTexture(Texture tex);
        const Texture& GetTexIndex(int index) const;
        const int GetTexSize() const;
};

#endif