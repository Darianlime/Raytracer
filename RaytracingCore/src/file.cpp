#include "file.h"

using std::ifstream;
using std::getline;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::to_string;

int File::ParseArgs(string inputFile, vector<vector<string>>& args, std::unordered_map<string, vector<float>> &argsMap)
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
        size_t firstChar = inputLine.find_first_not_of(" \t");
        if (firstChar == std::string::npos || inputLine[firstChar] == '#') {
            continue;
        }

        std::stringstream input(inputLine);
        string keyword;
        
        getline(input, keyword, ' ');
        args.push_back({});
        args[index].push_back(keyword);
        argsMap[keyword] = vector<float>();

        string arg;
        while (getline(input, arg, ' ')) {
            args[index].push_back(arg);
            float value;
            auto result = std::from_chars(arg.data(), arg.data() + arg.size(), value);
            if (result.ec == std::errc()) {
                argsMap[keyword].push_back(value);
            }
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

int File::ReadOBJ(string inputFileName, int matIndex, int texIndex, ObjectFactory& objectFactory)
{
    ifstream fin(inputFileName);
    if (!fin.is_open()) {
        cerr << "Error creating obj file" << endl;
        return -1;
    }

    string inputLine;
    int index = 0;
    while (getline(fin, inputLine, '\n'))
    {
        std::vector<string> args{};
        size_t firstChar = inputLine.find_first_not_of(" \t");
        if (firstChar == std::string::npos || inputLine[firstChar] == '#') {
            continue;
        }

        std::stringstream input(inputLine);
        string keyword;
        
        getline(input, keyword, ' ');

        string arg;
        while (getline(input, arg, ' ')) {
            args.push_back(arg);
        }
        args.push_back(to_string(matIndex));
        args.push_back(to_string(texIndex));
        objectFactory.GetFactory<ModelFactory>().CreateObject(keyword, args);
        cout << "Input line OBJ: " << inputLine << endl;
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


int File::ReadPPMBinary(string inputFileName, int &width, int &height, vector<Color> &pixels) {
    std::cout << "reading p6" << std::endl;
    ifstream fin(inputFileName, std::ios::binary);
    if (!fin.is_open()) {
        cerr << "Error opening read file" << endl;
        return -1;
    }
    string format;
    int maxRGBValue;

    fin >> format >> width >> height >> maxRGBValue;
    fin.ignore(1); // skip newline after header

    pixels.resize(width * height);

    for (int i = 0; i < width * height; i++) {
        unsigned char rgb[3];
        fin.read(reinterpret_cast<char*>(rgb), 3);

        pixels[i].r = rgb[0];
        pixels[i].g = rgb[1];
        pixels[i].b = rgb[2];
    }
    fin.close();
    return 0;
}

int File::ReadPPM(string inputFileName, int &width, int &height, vector<Color> &pixels) {
    ifstream fin(inputFileName);
    if (!fin.is_open()) {
        cerr << "Error opening read file" << endl;
        return -1;
    }
    string format{};
    int maxRGBValue{};
    fin >> format >> width >> height >> maxRGBValue;
    if (format == "P6") {
        fin.close();
        ReadPPMBinary(inputFileName, width, height, pixels);
        return 0;
    }
    pixels.resize(width * height); 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Color pixel;
            fin >> pixel.r >> pixel.g >> pixel.b;
            pixels[i * width + j] = pixel;
        }
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

int File::VaildateArgs(std::unordered_map<string, vector<float>>& args)
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
    if (args["vfov"][0] < 0 || args["vfov"][0] > 180) { cerr << "Error: vfov is less than 0 or greater than 180" << endl; return -1; }
    if (Color(args["bkgcolor"][0], args["bkgcolor"][1], args["bkgcolor"][2], true).CheckArgs() == -1) { return -1; }

    return 0;
}

int File::VaildateObjectsArgs(vector<vector<string>>& args, ObjectFactory& objectFactory) {
    Material mtl{};
    Texture tex{};
    int matIndex = -1, texIndex = -1;
    for (int i = 0; i < args.size(); i++) {
        string id = args[i][0];
        if (id == "mtlcolor") {
            mtl = Material(
                Color(stof(args[i][1]), stof(args[i][2]), stof(args[i][3]), false),
                Color(stof(args[i][4]), stof(args[i][5]), stof(args[i][6]), false), 
                Vec3(stof(args[i][7]), stof(args[i][8]), stof(args[i][9])),
                stof(args[i][10]),
                Color(stof(args[i][11]), stof(args[i][12]), stof(args[i][13]), false),
                stof(args[i][14])
            );
            objectFactory.AddMaterial(mtl);
            matIndex++;
            // if (mtl.CheckArgs() == -1) {
            //     return -1;
            // }
        } else if (id == "texture") {
            std::vector<Color> pixels;
            int width{}, height{};
            File::ReadPPM(args[i][1], width, height, pixels);
            tex = Texture(width, height, pixels);
            objectFactory.AddTexture(tex);
            texIndex++;
        } else if (id == "obj") {
            objectFactory.GetFactory<ModelFactory>().ResetCurrentVertexStart();
            File::ReadOBJ(args[i][1], matIndex, texIndex, objectFactory);
        } else {
            vector<string> arg = args[i];
            arg.erase(arg.begin());
            arg.emplace_back(to_string(matIndex));
            arg.emplace_back(to_string(texIndex));
            for (auto& factory : objectFactory.GetFactoryMap()) {
                factory.second.get()->CreateObject(id, arg);
            }
        }
    }
    return 0;
}