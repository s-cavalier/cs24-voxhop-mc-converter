#include <cstdio>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "USAGE: ./path [data.log] [interval]" << endl;
        return 1;
    }

    fstream log;
    log.open(argv[1]);
    if (log.fail()) {
        cout << "Error opening " << argv[1] << endl;
        return 1;
    }

    fstream mcfile;
    remove("./_insert_path.mcfunction");
    mcfile.open("./_insert_path.mcfunction", ios::out);
    if (mcfile.fail()) {
        cout << "Error opening _insert_path.mcfunction." << endl;
        return 1;
    }

    int interval = stoi(argv[2]);
    if (interval < 0) {
        cout << "Interval must be non-negative." << endl;
        return 1;
    }

    string line;
    size_t i = 0;

    while (getline(log, line)) {
        stringstream splitter(line);
        string block = " ";
        string temp;
        splitter >> temp;
        int x = stol(temp);
        splitter >> temp;
        int z = stol(temp);
        splitter >> temp;
        int y = stol(temp);
        if (splitter.eof()) block += "gold_block";
        else {
            splitter >> temp;
            block += temp;
        }

        
        mcfile << "execute if score .tick timer matches " << i << " run setblock ~" << x << " ~" << y << " ~" << z << block << endl;
        i += interval;
    }

    mcfile << "execute if score .tick timer matches " << i << " run kill @e[type=marker, tag=start]" << endl;
    mcfile << "execute if score .tick timer matches " << i + interval << " run scoreboard players set bool .exec 0" << endl;
}