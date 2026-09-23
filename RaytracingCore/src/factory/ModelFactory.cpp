#include "factory/ModelFactory.h"
using std::function;

ModelFactory::ModelFactory() : currentVertexStart(0), indexOfCurrentMesh(-1) {
    modelMap["sphere"] = [](vector<float>& args) { return make_unique<Sphere>(args); };
    modelMap["cylinder"] = [](vector<float>& args) { return make_unique<Cylinder>(args); };
    modelMap["cone"] = [](vector<float>& args) { return make_unique<Cone>(args); };
    modelMap["ellipsoid"] = [](vector<float>& args) { return make_unique<Ellipsoid>(args); };  

    geometryMap["v"] = [this](vector<float>& args) { AddVertPos(args); };
    geometryMap["vn"] = [this](vector<float>& args) { AddVertNormal(args); };
    geometryMap["vt"] = [this](vector<float>& args) { AddVertTex(args); };
}

void ModelFactory::AddVertPos(vector<float>& args) {
    vertsPos.emplace_back(args[0],args[1],args[2]);
    objects[indexOfCurrentMesh]->pos = objects[indexOfCurrentMesh]->pos * objects[indexOfCurrentMesh]->GetVertices().size();
    objects[indexOfCurrentMesh]->GetVertices().emplace_back();
    objects[indexOfCurrentMesh]->GetVertices().back().pos = Vec3(args[0],args[1],args[2]);
    objects[indexOfCurrentMesh]->GetOrgVertices().emplace_back();
    objects[indexOfCurrentMesh]->GetOrgVertices().back().pos = Vec3(args[0],args[1],args[2]);
    objects[indexOfCurrentMesh]->pos = (objects[indexOfCurrentMesh]->pos + Vec3(args[0],args[1],args[2])) / objects[indexOfCurrentMesh]->GetVertices().size();
}

void ModelFactory::AddVertNormal(vector<float>& args) {
    vertsNormal.emplace_back(args[0],args[1],args[2]);
    //objects[indexOfCurrentMesh]->GetVertices()[normalIndex].normal = Vec3(args[0],args[1],args[2]);
    //normalIndex++;
}

void ModelFactory::AddVertTex(vector<float>& args) {
    vertsTex.emplace_back(args[0],args[1]);
    //objects[indexOfCurrentMesh]->GetVertices()[texIndex].texture = Vec2(args[0],args[1]);
    //texIndex++;
}

void ModelFactory::AddIndice(vector<int>& args) {
    if (indexOfCurrentMesh != -1) {
        objects[indexOfCurrentMesh]->GetTriangles().emplace_back(args);
    }
}

void ModelFactory::AddMesh(string name, vector<int> modelArgs) {
    if (indexOfCurrentMesh > -1 && isAddingToVertCount) {
        currentVertexStart += objects[indexOfCurrentMesh]->GetVertices().size();
    }
    isAddingToVertCount = true;
    indexOfCurrentMesh = objects.size();
    for (int args : modelArgs) { std::cout << "modelArgs: " << args << std::endl; }
    objects.push_back(make_unique<Mesh>(name, modelArgs));
}

void ModelFactory::ResetCurrentVertexStart()
{
    vertsPos.clear();
    normalIndex = 0;
    texIndex = 0;
    vertsNormal.clear();
    vertsTex.clear();
    currentVertexStart = 0;
    isAddingToVertCount = false;
}

int ModelFactory::CreateObject(string &objectName, vector<string> &args)
{
    // create meshs            
    if (objectName == "o") {
        vector<int> modelArgs = {stoi(args[args.size()-2]), -1};
        //if (stoi(args[args.size()-2])) { }
        // for (int i = 1; i < modelArgs.size(); i++) {
        //     modelArgs[i] = stoi(args[i]);
        // }
        std::cout << "o: mesh created: " << stoi(args[args.size()-2]) << stoi(args[args.size()-1]) << std::endl;
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
        for (int i = 0; i < vertsArgs.size(); i++) {
            vertsArgs[i] = stof(args[i]); 
        } 
        if (indexOfCurrentMesh == -1 && vertsPos.empty()) {
            std::cout << "mesh created " << (int)vertsArgs[vertsArgs.size()-2] << " + "<< (int)vertsArgs[vertsArgs.size()-1] << std::endl;
            vector<int> modelArgs = {(int)vertsArgs[vertsArgs.size()-2], (int)vertsArgs[vertsArgs.size()-1]};
            AddMesh("mesh", modelArgs);
        }
        geometryMap[objectName](vertsArgs);
        return 0;
    }

    // Is Shade Smoothing On?
    if (objectName == "s") {
        std::cout << "smoothing on: " << stoi(args[0]) << std::endl;
        if (stoi(args[0]) == 1) {
            objects[indexOfCurrentMesh]->isSmoothShadingOn = true;
        }
        return 0;
    }

    if (objectName == "f") {
        vector<int> vertsArgs{stoi(args[args.size()-2]), stoi(args[args.size()-1]), 0};
        AddIndice(vertsArgs);
        ModelFactory::ParseTriangle(args, vertsArgs);
    }
    return 0;
}

void ModelFactory::RemoveModel(int index) {
    objects.erase(objects.begin() + index);
}

int ModelFactory::ChangeNegativeIndices(int index, int count) {
    if (index > 0) { 
        return index - 1; 
    }
    return count + index;
}

void ModelFactory::ParseTriangle(vector<string>& args, vector<int>& vertsArgs) {
    const int INDICE_SIZE = 3;
    const int EXTRA_ARGS = 3;
    //vertsArgs.resize((args.size()-2) * INDICE_SIZE + EXTRA_ARGS, -1);
    bool texPresent = false;
    bool normalPresent = false;
    Triangle& tri = objects[indexOfCurrentMesh]->GetTriangles().back();
    Indices indice;
    for (int i = 0; i < INDICE_SIZE; i++) {
        const char* toChar = args[i].c_str();
        const char* ptr = args[i].c_str();
        const char* end = toChar + strlen(toChar);
        int v = 0, vn = 0, vt = 0;
        std::from_chars_result res = std::from_chars(ptr, end, v);
        ptr = res.ptr;

        int vertexIndex = ChangeNegativeIndices(v, vertsPos.size());

        if (*ptr == '/') {
            ptr++;
            if (*ptr != '/') {
                std::from_chars_result res = std::from_chars(ptr, end, vt);
                int texIndex = ChangeNegativeIndices(vt, vertsTex.size());
                objects[indexOfCurrentMesh]->GetVertices()[vertexIndex - currentVertexStart].texture = vertsTex[texIndex - currentVertexStart];
                objects[indexOfCurrentMesh]->GetOrgVertices()[vertexIndex - currentVertexStart].texture = vertsTex[texIndex - currentVertexStart];
                ptr = res.ptr;
                texPresent = true;
            }
            if (*ptr == '/') {
                ptr++;
                std::from_chars(ptr, end, vn);
				int normalIndex = ChangeNegativeIndices(vn, vertsNormal.size());
                objects[indexOfCurrentMesh]->GetVertices()[vertexIndex - currentVertexStart].normal = vertsNormal[normalIndex - currentVertexStart];
                objects[indexOfCurrentMesh]->GetOrgVertices()[vertexIndex - currentVertexStart].normal = vertsNormal[normalIndex - currentVertexStart];
                normalPresent = true;
            }
        }
        tri.SetVertex(&objects[indexOfCurrentMesh]->GetVertices()[vertexIndex - currentVertexStart], i);
    }
    tri.CacheCalculations();
    //vertsArgs[vertsArgs.size()-EXTRA_ARGS] = stoi(args[args.size()-2]);
    //vertsArgs[vertsArgs.size()-(EXTRA_ARGS-1)] = stoi(args[args.size()-1]);
    //vertsArgs[vertsArgs.size()-(EXTRA_ARGS-2)] = texPresent + (normalPresent << 1);
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