#include "factory/ModelFactory.h"
using std::function;

ModelFactory::ModelFactory() : indexOfCurrentMesh(-1) {
    modelMap["sphere"] = [](vector<float>& args) { return make_unique<Sphere>(args); };
    modelMap["cylinder"] = [](vector<float>& args) { return make_unique<Cylinder>(args); };
    modelMap["cone"] = [](vector<float>& args) { return make_unique<Cone>(args); };
    modelMap["ellipsoid"] = [](vector<float>& args) { return make_unique<Ellipsoid>(args); };  

    geometryMap["f"] = [this](vector<float>& args) { AddIndice(args); };
    geometryMap["v"] = [this](vector<float>& args) { AddVertPos(args); };
    geometryMap["vn"] = [this](vector<float>& args) { AddVertNormal(args); };
    geometryMap["vt"] = [this](vector<float>& args) { AddVertTex(args); };
}

void ModelFactory::AddVertPos(vector<float>& args) {
    vertsPos.emplace_back(args[0],args[1],args[2]);
}

void ModelFactory::AddVertNormal(vector<float>& args) {
    vertsNormal.emplace_back(args[0],args[1],args[2]);
}

void ModelFactory::AddVertTex(vector<float>& args) {
    vertsTex.emplace_back(args[0],args[1]);
}

void ModelFactory::AddIndice(vector<float>& args) {
    objects.push_back(make_unique<Triangle>(args));
    // if (indexOfCurrentMesh != -1) {
    //     objects[indexOfCurrentMesh]->GetTriangles().emplace_back(args);
    // }
}

void ModelFactory::AddMesh(string name, vector<int> modelArgs) {
    //indexOfCurrentMesh = objects.size();
    //objects.push_back(make_unique<Mesh>(name, modelArgs));
}

int ModelFactory::CreateObject(string &objectName, vector<string> &args)
{
    // create meshs
    if (objectName == "o") {
        vector<int> modelArgs = {-1, -1};
        // for (int i = 1; i < modelArgs.size(); i++) {
        //     modelArgs[i] = stoi(args[i]);
        // }
        std::cout << "o: mesh created" << std::endl;
        AddMesh(args[0], modelArgs);
        return 0;
    }

    if (modelMap.find(objectName) != modelMap.end()) {
        vector<float> modelArgs(args.size());
        for (int i = 0; i < modelArgs.size(); i++) {
            modelArgs[i] = stof(args[i]);
        }
        objects.push_back(modelMap[objectName](modelArgs));
        return 0;
    }

    // create geometry
    auto geoIndex = geometryMap.find(objectName);
    if (geoIndex != geometryMap.end()) {
        vector<float> vertsArgs(args.size());
        // parse triangle
        if (geoIndex->first == "f") {
            ModelFactory::ParseTriangle(args, vertsArgs);
        } else {
            for (int i = 0; i < vertsArgs.size(); i++) {
                vertsArgs[i] = stof(args[i]); 
            }      
            if (vertsPos.size() == 0 && indexOfCurrentMesh == -1) {
                std::cout << "mesh created" << std::endl;
                vector<int> modelArgs = {(int)vertsArgs[vertsArgs.size()-2], (int)vertsArgs[vertsArgs.size()-1]};
                AddMesh("mesh", modelArgs);
            }
        }
        geometryMap[objectName](vertsArgs);
    }
    return 0;
}

void ModelFactory::RemoveModel(int index) {
    objects.erase(objects.begin() + index);
}

void ModelFactory::ParseTriangle(vector<string> &args, vector<float>& vertsArgs) {

    const int INDICE_SIZE = 8;
    const int EXTRA_ARGS = 3;
    vertsArgs.resize((args.size()-2) * INDICE_SIZE + EXTRA_ARGS);
    bool texPresent = false;
    bool normalPresent = false;
    for (int i = 0; i < args.size()-2; i++) {
        const char* toChar = args[i].c_str();
        const char* ptr = toChar;
        const char* end = toChar + strlen(toChar);
        int v, vn, vt;
        int index = i*INDICE_SIZE;
        std::from_chars_result res = std::from_chars(ptr, end, v);
        vertsArgs[index] = vertsPos[v-1].x;
        vertsArgs[index+1] = vertsPos[v-1].y;
        vertsArgs[index+2] = vertsPos[v-1].z;
        ptr = res.ptr;
        if (*ptr == '/') {
            ptr++;
            if (*ptr != '/') {
                std::from_chars_result res = std::from_chars(ptr, end, vt);
                vertsArgs[index+6] = vertsTex[vt-1].x;
                vertsArgs[index+7] = vertsTex[vt-1].y;
                ptr = res.ptr;
                texPresent = true;
            }
            if (*ptr == '/') {
                ptr++;
                std::from_chars(ptr, end, vn);
                vertsArgs[index+3] = vertsNormal[vn-1].x;
                vertsArgs[index+4] = vertsNormal[vn-1].y;
                vertsArgs[index+5] = vertsNormal[vn-1].z;
                normalPresent = true;
            }
        }
    }
    vertsArgs[vertsArgs.size()-EXTRA_ARGS] = stoi(args[args.size()-2]);
    vertsArgs[vertsArgs.size()-(EXTRA_ARGS-1)] = stoi(args[args.size()-1]);
    vertsArgs[vertsArgs.size()-(EXTRA_ARGS-2)] = texPresent + (normalPresent << 1);
}

string ModelFactory::GetTypeIndex(int index)
{
    ModelType type = static_cast<ModelType>(index);
    return Model::GetTypeMap()[type];
}

int ModelFactory::GetTypeMapSize()
{
    return Model::GetTypeMap().size();
}

map<string, function<unique_ptr<Model>(vector<float> &)>> &ModelFactory::GetModelMap()
{
    return modelMap;
}

map<string, function<void(vector<float>&)>> &ModelFactory::GetGeometryMap()
{
    return geometryMap;
}