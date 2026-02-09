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
#include "include/objects/sphere.h" 

using namespace std;

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        cout << "argv[" << i << "]: " << argv[i] << endl;
    }

    string inputFile = argv[1];
    string extension = "";

    // Validate input file extension
    size_t index = inputFile.find_last_of('.');
    string nameFile = inputFile.substr(0, index);
    string extFile = inputFile.substr(index + 1);

    if (index != string::npos) {
        if (extFile != "txt") {
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

    cout << "imsize: " + argsCamera.find("imsize")->second[0] << endl;
    for (int i = 0; i < argsCamera["imsize"].size(); i++) {
        cout << "argsCamera: " + argsCamera["imsize"][i] << endl;
    }

    Vec3 eye(stof(argsCamera["eye"][0]), stof(argsCamera["eye"][1]), stof(argsCamera["eye"][2]));
    Vec3 viewdir(stof(argsCamera["viewdir"][0]), stof(argsCamera["viewdir"][1]), stof(argsCamera["viewdir"][2]));
    Vec3 updir(stof(argsCamera["updir"][0]), stof(argsCamera["updir"][1]), stof(argsCamera["updir"][2]));
    Camera cam(eye, viewdir, updir, stof(argsCamera["vfov"][0]));

    cout << "cam u: " << cam.GetU().x << " + " << cam.GetU().y << " + " << cam.GetU().z << endl;
    cout << "cam v: " << cam.GetV().x << " + " << cam.GetV().y << " + " << cam.GetV().z << endl;

    Color bkg(stof(argsCamera["bkgcolor"][0]), stof(argsCamera["bkgcolor"][1]), stof(argsCamera["bkgcolor"][2]), true);
    Screen screen(stoi(argsCamera["imsize"][0]), stoi(argsCamera["imsize"][1]), bkg);
    screen.CalcWindowCorners(cam);

    cout << screen.GetDH().x << " + " << screen.GetDH().y <<  " + " << screen.GetDH().z << endl;
    cout << screen.GetDV().x << " + " << screen.GetDV().y <<  " + " << screen.GetDV().z << endl;
    cout << screen.GetWindowLocation(300,1).x << " + " << screen.GetWindowLocation(300,1).y <<  " + " << screen.GetWindowLocation(300,1).z << endl;
    
    Raycast ray(eye);

    Object* sphere = new Sphere(
        Vec3(stof(args[firstMTLIndex+1][1]), stof(args[firstMTLIndex+1][2]), stof(args[firstMTLIndex+1][3])),
        stof(args[firstMTLIndex+1][4]),
        Color(stof(args[firstMTLIndex][1]), stof(args[firstMTLIndex][2]), stof(args[firstMTLIndex][3]), true)
    );

    pair<Vec3, bool> intersection = sphere->CheckIntersection(ray);
    cout << "object name: " << sphere->GetName() << " " << sphere->mat.r << sphere->mat.g <<  endl;
    //cout << "intersection: " << intersection.first.x << " + " << intersection.first.y << " + " << intersection.first.z << " bool: " << intersection.second << endl;



    // auto it = argsCamera.find("mtlcolor");
    // cout << "mtcolor: " << it->first << endl;
    // ++it;
    // cout << "sphere: " << it->first << endl;
    vector<vector<Color>>& pixels = screen.GetPixels();
    int h = screen.GetHeight();
    int w = screen.GetWidth();

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            //cout << i << " " << j << endl;
            ray.SetRayDirAtPoint(screen.GetWindowLocation(j,i));
            Color color = ray.TraceRay(Vec3(0,0,0), screen.bkgcolor);
            pixels[i][j] = color;
        }
    }

    return 0;
}