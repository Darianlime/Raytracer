#include "file.h"

int File::ParseArgs(string inputFile, unordered_map<string, vector<string>>& args)
{
    // Open and read input file
    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cerr << "Error creating input file" << endl;
        return -1;
    }

    // get inputs from file and add to vector
    string inputLine;
    vector<string> sameArg;
    int sameIndex = 0;
    while (getline(fin, inputLine, '\n'))
    {
        stringstream input(inputLine);
        string keyword;
        
        getline(input, keyword, ' ');

        if (find(sameArg.begin(), sameArg.end(), keyword) != sameArg.end()) {
            sameIndex++;
            keyword += to_string(sameIndex);
            args[keyword] = vector<string>();
        }
        else {
            sameArg.push_back(keyword);
            args[keyword] = vector<string>();
        }

        string arg;

        while (getline(input, arg, ' ')) {
            args[keyword].push_back(arg);
        }
        cout << "Input line: " << inputLine << endl;
    }

    if (fin.eof()) {
        cout << "Reached end of file." << endl;
    }
    else {
        cerr << "Error: File reading failed!" << endl;
        return -1;
    }

    fin.close();
    return 0;
}