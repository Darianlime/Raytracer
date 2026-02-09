#ifndef FILE_H
#define FILE_H

#include "color.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class File {
    private:

    public:
        File();

        static int ParseArgs(string inputFile, vector<vector<string>>& map);
        static int WritePixels(vector<vector<Color>>& pixels);
        static int FindKeyIndex(vector<vector<string>>& map, string key);
}; 

#endif