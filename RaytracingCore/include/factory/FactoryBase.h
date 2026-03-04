#ifndef FACTORY_BASE_H
#define FACTORY_BASE_H

#include "IFactory.h"
#include "object.h"
#include "material.h"
#include <memory>
#include <functional>
#include <charconv>
#include <cstring>

using std::unique_ptr;
using std::make_unique;

// Generic class used to get the objects in the other factories
template <typename T>
class FactoryBase : public IFactory {
    protected:
        vector<unique_ptr<T>> objects;
    public:
        FactoryBase() {} 
        virtual vector<unique_ptr<T>>& GetObjects() { return objects; } 
        int CreateObject(string& objectName, vector<string>& args) override {
            std::cout << "creating obj in base" << std::endl;
            return 0;
        };

        string GetName() override {
            return "Factory Base";
        };
}; 

#endif