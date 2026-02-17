#ifndef I_FACTORY_H
#define I_FACTORY_H

#include <string>
#include <vector>
using namespace std;

class IFactory {
    public:
        virtual ~IFactory() = default;
        virtual int CreateObject(string& objectName, vector<string>& args) = 0;
};

#endif