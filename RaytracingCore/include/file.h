#ifndef FILE_H
#define FILE_H

#include "color.h"
#include "factory/ObjectFactory.h"
#include "factory/ModelFactory.h"
#include "factory/LightFactory.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
 
class File {
    public:
        static int ParseArgs(string inputFile, vector<vector<string>> &args, std::unordered_map<string, vector<float>> &argsMap);
        static int ReadOBJ(string inputFileName, ObjectFactory &objectFactory);
        static int ReadPPMBinary(string inputFileName, int &width, int &height, vector<Color> &pixels);
        static int ReadPPM(string inputFileName, int &width, int &height, vector<Color> &pixels);
        static int WriteToPPM(string inputFileName, vector<vector<Color>> &pixels);
        static int FindKeyIndex(vector<vector<string>>& map, string key);
        static int VaildateArgs(std::unordered_map<string, vector<float>>& args);
        static int VaildateObjectsArgs(vector<vector<string>>& args, ObjectFactory& objectFactory);
};

#endif