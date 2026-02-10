#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "include/vector.h"
#include "include/file.h"
#include "include/camera.h"
#include "include/screen.h"
#include "include/raycast.h" 
#include "include/factory/ObjectFactory.h"

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
    int firstMTLIndex = 0;
    if (File::ParseArgs(inputFile, args) == -1) {
        cerr << "Failed to get args in file" << endl;
        return 1;
    }
    if ((firstMTLIndex = File::FindKeyIndex(args, "mtlcolor")) == -1) {
        cerr << "Failed to get first material color" << endl;
        return 1;
    }
    cout << "index: " << firstMTLIndex << endl;
    for (int i = 0; i < firstMTLIndex; i++) {
        string key = args[i][0];
        argsCamera[key] = vector<string>();
        //cout << key + " ";
        for (int j = 1; j < args[i].size(); j++) {
            argsCamera[key].push_back(args[i][j]);
            //cout << argsCamera[key].back() + " ";
        }
        //cout << endl;
    }

    ObjectFactory objectFactory;

    Color mtl;
    for (int i = firstMTLIndex; i < args.size(); i++) {
        string id = args[i][0];
        if (id == "mtlcolor") {
            mtl = Color(stof(args[i][1]), stof(args[i][2]), stof(args[i][3]), true);
        } else {
            vector<string> objectVal = args[i];
            objectVal.erase(objectVal.begin());
            objectFactory.CreateObject(id, objectVal, mtl);
        }
    }

    for (int i = 0; i < objectFactory.GetObjects().size(); i++) {
        cout << objectFactory.GetObjects()[i]->GetName() << endl;
    }

    cout << "imsize: " + argsCamera.find("imsize")->second[0] << endl;
    for (int i = 0; i < argsCamera["imsize"].size(); i++) {
        cout << "argsCamera: " + argsCamera["imsize"][i] << endl;
    }

    Vec3 eye(stof(argsCamera["eye"][0]), stof(argsCamera["eye"][1]), stof(argsCamera["eye"][2]));
    Vec3 viewdir(stof(argsCamera["viewdir"][0]), stof(argsCamera["viewdir"][1]), stof(argsCamera["viewdir"][2]));
    Vec3 updir(stof(argsCamera["updir"][0]), stof(argsCamera["updir"][1]), stof(argsCamera["updir"][2]));
    Camera cam(eye, viewdir, updir, stof(argsCamera["vfov"][0]));

    Color bkg(stof(argsCamera["bkgcolor"][0]), stof(argsCamera["bkgcolor"][1]), stof(argsCamera["bkgcolor"][2]), true);
    Screen screen(stoi(argsCamera["imsize"][0]), stoi(argsCamera["imsize"][1]), bkg);
    screen.CalcWindowCorners(cam);
    
    Raycast ray(eye);

    vector<vector<Color>>& pixels = screen.GetPixels();
    int h = screen.GetHeight();
    int w = screen.GetWidth();
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            Color color = ray.TraceRay(screen.GetWindowLocation(j,i), bkg, objectFactory.GetObjects());
            pixels[j][i] = color;
        }
    }

    if (File::WriteToPPM(fileName, pixels) == -1) {
        cerr << "Failed to write to " << fileName << endl;
        return 1;
    }
    return 0;
}