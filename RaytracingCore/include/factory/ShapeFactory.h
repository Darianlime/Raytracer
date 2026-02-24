#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include <vector>
#include "factory/FactoryBase.h"
#include "shapes/sphere.h"
#include "shapes/cylinder.h"
#include "shapes/cone.h"
#include "shapes/ellipsoid.h"

class ShapeFactory : public FactoryBase<Shape> {
    public:
        ShapeFactory();
        ~ShapeFactory() {};
        int CreateObject(string& objectName, vector<string>& args) override;
        //Object* CreateObject(ObjectType objectType, vector<string> args, Material mat); 
};

#endif