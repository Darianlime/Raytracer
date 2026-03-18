#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "factory/LightFactory.h"
#include "factory/MeshFactory.h"
#include "material.h"
#include "texture.h"

// Factory to create new object factories
class ObjectFactory {
    private:
        std::unordered_map<std::type_index, unique_ptr<IFactory>> factories;
        
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
        T& GetFactory() {
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

        void AddMaterial(Material mat);
        void AddTexture(Texture tex);
        const vector<Material> &GetMats() const;
        const int GetMatsSize() const;
        Material& GetMatIndex(int index);
        const Material& GetMatIndex(int index) const;

        Texture& GetTexIndex(int index);
        const int GetTexSize() const;
};

#endif