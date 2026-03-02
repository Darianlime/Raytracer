#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "include/vector.h"
#include "include/file.h"
#include "include/camera.h"
#include "include/viewport.h"
#include "include/raycast.h" 

using namespace std;
using namespace Raytracer;

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        cout << "argv[" << i << "]: " << argv[i] << endl;
    }

    string inputFile = argv[1];
    string extension = "";

    // Validate input file extension
    size_t index = inputFile.find_last_of('.');
    string fileName = inputFile.substr(0, index);
    string fileExt = inputFile.substr(index + 1);

    if (index != string::npos) {
        if (fileExt != "txt") {
            cerr << "Input file must be a .txt file" << endl;
            return 1;
        }
    }
    else {
        cerr << "Input file must be a .txt file" << endl;
        return 1;
    }

    // store arguments in a 2d vector and map
    vector<vector<string>> args;
    unordered_map<string, vector<float>> argsMap;
    if (File::ParseArgs(inputFile, args, argsMap) == -1) {
        cerr << "Failed to get args in file" << endl;
        return 1;
    }

    // Check if Arguments are vaild
    if (File::VaildateArgs(argsMap) == -1) {
        return 1;
    }

    // Store shapes and objects inside the object factory
    ObjectFactory objectFactory;
    objectFactory.CreateFactory<MeshFactory>();
    objectFactory.CreateFactory<LightFactory>();
    if (File::VaildateObjectsArgs(args, objectFactory) == -1) {
        return 1;
    }

    for (auto& shape : objectFactory.GetFactory<MeshFactory>().GetObjects()) {
        cout << shape->GetName() << endl;
    }

    Camera cam(
        Vec3(argsMap["eye"][0], argsMap["eye"][1], argsMap["eye"][2]),
        Vec3(argsMap["viewdir"][0], argsMap["viewdir"][1], argsMap["viewdir"][2]),
        Vec3(argsMap["updir"][0], argsMap["updir"][1], argsMap["updir"][2]),
        argsMap["vfov"][0]);

    Viewport screen(argsMap["imsize"][0], argsMap["imsize"][1], Color(argsMap["bkgcolor"][0], argsMap["bkgcolor"][1], argsMap["bkgcolor"][2], false));
    screen.CalcWindowCorners(cam);
    
    Raycast ray(Vec3(argsMap["eye"][0], argsMap["eye"][1], argsMap["eye"][2]));

    // If Depthcueing is enabled store arguments
    Color depthCueColor;
    float alphaMin, alphaMax, depthFar, depthNear;
    if (argsMap.find("depthcueing") != argsMap.end()) {
        depthCueColor = Color(argsMap["depthcueing"][0], argsMap["depthcueing"][1], argsMap["depthcueing"][2], false);
        alphaMin = argsMap["depthcueing"][3];
        alphaMax = argsMap["depthcueing"][4];
        depthNear = argsMap["depthcueing"][5];
        depthFar = argsMap["depthcueing"][6];
    }

    vector<vector<Color>>& pixels = screen.GetPixels();
    int h = screen.GetHeight();
    int w = screen.GetWidth();
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            float alphaDepthCue = 1.0f;
            pair<Vec3, bool> intersectedPoint(Vec3(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity()), false);
            Color color = ray.TraceRay(screen.GetWindowLocation(j,i), screen.bkgcolor, objectFactory, intersectedPoint);
            // Calculate for deothcueing if enabled
            if (argsMap.find("depthcueing") != argsMap.end() && intersectedPoint.second) {
                float distObj = Vec3::Dist(intersectedPoint.first, ray.GetEye());
                if (distObj >= depthFar) { alphaDepthCue = alphaMin; }
                else if (distObj <= depthNear) { alphaDepthCue = alphaMax; }
                else { alphaDepthCue = alphaMin + (alphaMax - alphaMin) * ((depthFar - distObj) / (depthFar - depthNear)); }

                color = Color(color.GetVec() * alphaDepthCue + depthCueColor.GetVec() * (1 - alphaDepthCue), false);  
            }
            pixels[j][i] = Color(color.GetVec(), true);
        }
    }
    
    if (File::WriteToPPM(fileName, pixels) == -1) {
        cerr << "Failed to write to " << fileName << endl;
        return 1;
    }
    return 0;
}