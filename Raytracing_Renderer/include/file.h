#ifndef FILE_H
#define FILE_H

#include "color.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class File {
    private:

    public:
        File();

        static int ParseArgs(string inputFile, vector<vector<string>>& map);
        static int WriteToPPM(string inputFileName, vector<vector<Color>>& pixels);
        static int FindKeyIndex(vector<vector<string>>& map, string key);
        static int VaildateCameraArgs(unordered_map<string, vector<string>>, Vec3& imsize, Vec3& eye, Vec3& viewdir, Vec3& updir, float& vfov, Color& bkg);
}; 

#endif