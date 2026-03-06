#include "factory/MeshFactory.h"

using std::function;

MeshFactory::MeshFactory() {
    meshMap["sphere"] = [](vector<float>& args) { return make_unique<Sphere>(args); };
    meshMap["cylinder"] = [](vector<float>& args) { return make_unique<Cylinder>(args); };
    meshMap["cone"] = [](vector<float>& args) { return make_unique<Cone>(args); };
    meshMap["ellipsoid"] = [](vector<float>& args) { return make_unique<Ellipsoid>(args); };  

    geometryMap["f"] = [this](vector<float>& args) { AddTriangle(args); };
    geometryMap["v"] = [this](vector<float>& args) { AddVertPos(args); };
    geometryMap["vn"] = [this](vector<float>& args) { AddVertNormal(args); };
    geometryMap["vt"] = [this](vector<float>& args) { AddVertTex(args); };
}

void MeshFactory::AddVertPos(vector<float>& args) {
    vertsPos.emplace_back(args[0],args[1],args[2]);
}

void MeshFactory::AddVertNormal(vector<float>& args) {
    vertsNormal.emplace_back(args[0],args[1],args[2]);
}

void MeshFactory::AddVertTex(vector<float>& args) {
    vertsTex.emplace_back(args[0],args[1]);
}

void MeshFactory::AddTriangle(vector<float>& args) {
    objects.push_back(make_unique<Triangle>(args));
}

int MeshFactory::CreateObject(string &objectName, vector<string> &args)
{
    // create meshs
    if (meshMap.find(objectName) != meshMap.end()) {
        vector<float> meshArgs(args.size());
        for (int i = 0; i < meshArgs.size(); i++) {
            meshArgs[i] = stof(args[i]);
        }
        objects.push_back(meshMap[objectName](meshArgs));
    }

    // create geometry
    auto geoIndex = geometryMap.find(objectName);
    if (geoIndex != geometryMap.end()) {
        vector<float> vertsArgs(args.size());
        // parse triangle
        if (geoIndex->first == "f") {
            MeshFactory::ParseTriangle(args, vertsArgs);
        } else {
            for (int i = 0; i < vertsArgs.size(); i++) {
                vertsArgs[i] = stof(args[i]);
            }           
        }
        geometryMap[objectName](vertsArgs);
    }
    return 0;
}

void MeshFactory::ParseTriangle(vector<string> &args, vector<float>& vertsArgs) {

    const int INDICE_SIZE = 8;
    const int EXTRA_ARGS = 3;
    vertsArgs.resize((args.size()-1) * INDICE_SIZE + EXTRA_ARGS);
    bool texPresent = false;
    bool normalPresent = false;
    for (int i = 0; i < args.size()-1; i++) {
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

string MeshFactory::GetTypeIndex(int index)
{
    MeshType type = static_cast<MeshType>(index);
    return Mesh::GetTypeMap()[type];
}

int MeshFactory::GetTypeMapSize()
{
    return Mesh::GetTypeMap().size();
}

map<string, function<unique_ptr<Mesh>(vector<float> &)>> &MeshFactory::GetMeshMap()
{
    return meshMap;
}

map<string, function<void(vector<float>&)>> &MeshFactory::GetGeometryMap()
{
    return geometryMap;
}