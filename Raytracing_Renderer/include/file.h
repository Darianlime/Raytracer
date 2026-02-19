#ifndef FILE_H
#define FILE_H

#include "color.h"
#include "factory/ObjectFactory.h"
#include "factory/ShapeFactory.h"
#include "factory/LightFactory.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class File {
    public:
        static int ParseArgs(string inputFile, vector<vector<string>>& map);
        static int WriteToPPM(string inputFileName, vector<vector<Color>>& pixels);
        static int FindKeyIndex(vector<vector<string>>& map, string key);
        static int VaildateArgs(unordered_map<string, vector<float>> args);
        static int VaildateObjectsArgs(vector<vector<string>> args, ShapeFactory& objFactory, LightFactory& lightFactory);
        static int VaildateObjectsArgs(vector<vector<string>> args, ObjectFactory& objectFactory);
};

#endif