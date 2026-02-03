#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "include/vector.h"
#include "include/file.h"
#include "include/camera.h"
#include "include/screen.h" 

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

    unordered_map<string, vector<string>> args;
    if (File::ParseArgs(inputFile, args) == -1) {
        cerr << "Failed to get args in file" << endl;
        return 1;
    }

    cout << "imsize: " + args.find("imsize")->second[0] << endl;
    for (int i = 0; i < args["imsize"].size(); i++) {
        cout << "args: " + args["imsize"][i] << endl;
    }

    Vec3 eye(stof(args["eye"][0]), stof(args["eye"][1]), stof(args["eye"][2]));
    Vec3 viewdir(stof(args["viewdir"][0]), stof(args["viewdir"][1]), stof(args["viewdir"][2]));
    Vec3 updir(stof(args["updir"][0]), stof(args["updir"][1]), stof(args["updir"][2]));
    Camera cam(eye, viewdir, updir, stof(args["vfov"][0]));

    cout << "cam u: " << cam.GetU().x << " + " << cam.GetU().y << " + " << cam.GetU().z << endl;
    cout << "cam v: " << cam.GetV().x << " + " << cam.GetV().y << " + " << cam.GetV().z << endl;

    Screen screen(stoi(args["imsize"][0]), stoi(args["imsize"][1]));
    screen.CalcWindowCorners(cam, 5);

    return 0;
}