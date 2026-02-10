#include "file.h"

int File::ParseArgs(string inputFile, vector<vector<string>>& args)
{
    // Open and read input file
    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cerr << "Error creating input file" << endl;
        return -1;
    }

    // get inputs from file and add to vector
    string inputLine;
    //vector<string> sameArg;
    //int sameIndex = 0;
    int index = 0;
    while (getline(fin, inputLine, '\n'))
    {
        if (inputLine.empty()) {
            continue;
        }
        stringstream input(inputLine);
        string keyword;
        
        getline(input, keyword, ' ');
        args.push_back({});
        args[index].push_back(keyword);

        string arg;
        while (getline(input, arg, ' ')) {
            //args[keyword].push_back(arg);
            args[index].push_back(arg);
        }
        index++;
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

int File::WriteToPPM(string inputFileName, vector<vector<Color>> &pixels)
{
    // Create and open output file
    FILE* file = fopen((inputFileName + ".ppm").c_str(), "w");
    if (file == NULL) {
        cerr << "Error opening file" << endl;
        return -1;
    }

    int w = pixels.size();
    int h = pixels[0].size();

    string header = "P3\n" + to_string(w) + " " + to_string(h) + "\n255\n";
    cout << header << endl;
    fwrite(header.c_str(), 1, header.size(), file);

    // Write pixel data to file
    for (int y = 0; y <  h; ++y) {
	    string colorsLine = "";
	    for (int x = 0; x < w; ++x) {
		    colorsLine += pixels[x][y].ToString();
	    }
	    colorsLine += "\n";
	    fwrite(colorsLine.c_str(), 1, colorsLine.size(), file);
    }

    fclose(file);
    return 0;
}

int File::FindKeyIndex(vector<vector<string>> &map, string key)
{
    for (int i = 0; i < map.size(); i++) {
        if (map[i][0] == key) {
            return i;
        }
    }
    return -1;
}
