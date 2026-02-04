#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef FILE_H
#define FILE_H

class File {
    private:

    public:
        File();

        static int ParseArgs(string inputFile, unordered_map<string, vector<string>>& map);
}; 

#endif