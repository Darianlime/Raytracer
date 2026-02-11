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

int File::VaildateCameraArgs(unordered_map<string, vector<string>> args, Vec3& imsize, Vec3& eye, Vec3& viewdir, Vec3& updir, float& vfov, Color& bkg)
{
    if (args["imsize"].size() < 2) { cerr << "Not enough arguments for imsize" << endl; return -1; }
    if (args["eye"].size() < 3) { cerr << "Not enough arguments for eye" << endl; return -1; }
    if (args["viewdir"].size() < 3) { cerr << "Not enough arguments for viewdir" << endl; return -1; }
    if (args["vfov"].size() < 1) { cerr << "Not enough arguments for vfov" << endl; return -1; }
    if (args["updir"].size() < 3) { cerr << "Not enough arguments for updir" << endl; return -1; }
    if (args["bkgcolor"].size() < 3) { cerr << "Not enough arguments for bkgcolor" << endl; return -1; }

    imsize = Vec3(stoi(args["imsize"][0]), stoi(args["imsize"][1]), 0);
    eye = Vec3(stof(args["eye"][0]), stof(args["eye"][1]), stof(args["eye"][2]));
    viewdir = Vec3(stof(args["viewdir"][0]), stof(args["viewdir"][1]), stof(args["viewdir"][2]));
    updir = Vec3(stof(args["updir"][0]), stof(args["updir"][1]), stof(args["updir"][2]));
    bkg = Color(stof(args["bkgcolor"][0]), stof(args["bkgcolor"][1]), stof(args["bkgcolor"][2]), true);
    vfov = stof(args["vfov"][0]);

    if (imsize.x < 1 || imsize.y < 1) { cerr << "Error: imsize arguments are too small" << endl; return -1; }
    if (Vec3::Dot(eye, updir) != 0) { cerr << "Error: eye and updir are not orthogonal" << endl; return -1; }
    if (vfov < 0 || vfov > 180) { cerr << "Error: vfov is less than 0 or greater than 180" << endl; return -1; }
    if (bkg.CheckArgs() == -1) { return -1; }

    return 0;
}
