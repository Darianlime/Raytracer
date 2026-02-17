#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "factory/LightFactory.h"
#include "factory/ShapeFactory.h"
#include "material.h"

using namespace std;

class ObjectFactory {
    private:
        unordered_map<type_index, unique_ptr<IFactory>> factories;
        vector<Material> materials;
    public:
        ObjectFactory();
        ~ObjectFactory() {};
        template <typename T> 
        void CreateFactory() {
            factories[typeid(T)] = make_unique<T>();
        }

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

        unordered_map<type_index, unique_ptr<IFactory>>& GetFactoryMap();

        void AddMaterial(Material mat);
        const vector<Material>& GetMats();
}; 

#endif