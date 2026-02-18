#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "include/vector.h"
#include "include/file.h"
#include "include/camera.h"
#include "include/screen.h"
#include "include/raycast.h" 

using namespace std;

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

    vector<vector<string>> args;
    unordered_map<string, vector<string>> argsCamera;
    int bkgIndex = 0;
    int firstLightIndex = 0;
    if (File::ParseArgs(inputFile, args) == -1) {
        cerr << "Failed to get args in file" << endl;
        return 1;
    }
    if ((bkgIndex = File::FindKeyIndex(args, "bkgcolor")) == -1) {
        cerr << "Failed to get first material color" << endl;
        return 1;
    }

    for (int i = 0; i <= bkgIndex; i++) {
        string key = args[i][0];
        argsCamera[key] = vector<string>();
        for (int j = 1; j < args[i].size(); j++) {
            argsCamera[key].push_back(args[i][j]);
        }
    }

    cout << "in" << endl;

    // Check if Camera Arguments are vaild
    Vec3 imsize, eye, viewdir, updir;
    float vfov;
    Color bkg;
    if (File::VaildateCameraArgs(argsCamera, imsize, eye, viewdir, updir, vfov, bkg) == -1) {
        return 1;
    }

    cout << "in" << endl;

    ObjectFactory objectFactory;
    objectFactory.CreateFactory<ShapeFactory>();
    objectFactory.CreateFactory<LightFactory>();
    if (File::VaildateObjectsArgs(args, objectFactory) == -1) {
        return 1;
    }

    cout << "in" << endl;

    for (auto& shape : objectFactory.GetFactory<ShapeFactory>().GetObjects()) {
        cout << shape->GetName() << endl;
        cout << shape->mat << endl;
    }

    for (auto& mats : objectFactory.GetMats()) {
        cout << mats.ToString() << endl;
    }

    cout << "in" << endl;

    Camera cam(eye, viewdir, updir, vfov);

    Screen screen(imsize.x, imsize.y, bkg);
    screen.CalcWindowCorners(cam);
    
    Raycast ray(eye);

    vector<vector<Color>>& pixels = screen.GetPixels();
    int h = screen.GetHeight();
    int w = screen.GetWidth();
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            Color color = ray.TraceRay(screen.GetWindowLocation(j,i), bkg, objectFactory);
            pixels[j][i] = color;
        }
    }
    
    if (File::WriteToPPM(fileName, pixels) == -1) {
        cerr << "Failed to write to " << fileName << endl;
        return 1;
    }
    return 0;
}