#include "file.h"

int File::ParseArgs(string inputFile, vector<vector<string>>& args, unordered_map<string, vector<float>> &argsMap)
{
    // Open and read input file
    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cerr << "Error creating input file" << endl;
        return -1;
    }

    // get inputs from file and add to vector and map
    string inputLine;
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
        argsMap[keyword] = vector<float>();

        string arg;
        while (getline(input, arg, ' ')) {
            args[index].push_back(arg);
            argsMap[keyword].push_back(stof(arg));
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

int File::VaildateArgs(unordered_map<string, vector<float>> args)
{
    if (args["imsize"].size() < 2) { cerr << "Not enough arguments for imsize" << endl; return -1; }
    if (args["eye"].size() < 3) { cerr << "Not enough arguments for eye" << endl; return -1; }
    if (args["viewdir"].size() < 3) { cerr << "Not enough arguments for viewdir" << endl; return -1; }
    if (args["vfov"].size() < 1) { cerr << "Not enough arguments for vfov" << endl; return -1; }
    if (args["updir"].size() < 3) { cerr << "Not enough arguments for updir" << endl; return -1; }
    if (args["bkgcolor"].size() < 3) { cerr << "Not enough arguments for bkgcolor" << endl; return -1; }
    if (args.find("depthcueing") != args.end()) {
        if (args["depthcueing"].size() < 7) { cerr << "Not enough arguments for depthcueing" << endl; return -1; }
    }

    if (args["imsize"][0] < 1 || args["imsize"][1] < 1) { cerr << "Error: imsize arguments are too small" << endl; return -1; }
    if (Vec3::Dot(Vec3(args["eye"][0], args["eye"][1], args["eye"][2]), Vec3(args["updir"][0], args["updir"][1], args["updir"][2])) != 0) { cerr << "Error: eye and updir are not orthogonal" << endl; return -1; }
    if (args["vfov"][0] < 0 || args["vfov"][0] > 180) { cerr << "Error: vfov is less than 0 or greater than 180" << endl; return -1; }
    if (Color(args["bkgcolor"][0], args["bkgcolor"][1], args["bkgcolor"][2], true).CheckArgs() == -1) { return -1; }

    return 0;
}

int File::VaildateObjectsArgs(vector<vector<string>> args, ObjectFactory& objectFactory) {
    Material mtl;
    int matIndex = -1;
    for (int i = 0; i < args.size(); i++) {
        string id = args[i][0];
        if (id == "mtlcolor") {
            mtl = Material(
                Color(stof(args[i][1]), stof(args[i][2]), stof(args[i][3]), false),
                Color(stof(args[i][4]), stof(args[i][5]), stof(args[i][6]), false), 
                Vec3(stof(args[i][7]), stof(args[i][8]), stof(args[i][9])),
                stof(args[i][10])
            );
            objectFactory.AddMaterial(mtl);
            matIndex++;
            // if (mtl.CheckArgs() == -1) {
            //     return -1;
            // }
        } else {
            vector<string> objectVal = args[i];
            objectVal.push_back(to_string(matIndex));
            for (auto& factory : objectFactory.GetFactoryMap()) {
                factory.second.get()->CreateObject(id, objectVal);
            }
        }
    }
    return 0;
}
