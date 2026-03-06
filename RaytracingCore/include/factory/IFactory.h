#ifndef I_FACTORY_H
#define I_FACTORY_H

#include <string>
#include <vector>
#include <map>

using std::string;

// Interface to create new objects in the scene
class IFactory {
    public:
        virtual ~IFactory() = default;
        virtual int CreateObject(string& objectName, std::vector<string>& args) = 0;
        virtual string GetTypeIndex(int index) = 0;
        virtual int GetTypeMapSize() = 0;        

        virtual string GetName() = 0;
};

#endif