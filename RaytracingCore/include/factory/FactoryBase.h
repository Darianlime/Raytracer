#ifndef FACTORY_BASE_H
#define FACTORY_BASE_H

#include "IFactory.h"
#include "object.h"
#include "material.h"

// Generic class used to get the objects in the other factories
template <typename T>
class FactoryBase : public IFactory {
    protected:
        vector<T*> objects;
    public:
        FactoryBase() {} 
        virtual const vector<T*>& GetObjects() const { return objects; } 
        int CreateObject(string& objectName, vector<float>& args) override {
            cout << "creating obj in base" << endl;
            return 0;
        };

        string GetName() override {
            return "Factory Base";
        };
}; 

#endif