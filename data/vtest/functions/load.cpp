#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <filesystem>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cout << "USAGE: ./load <directory of .vox files>" << endl;
        return 1;
    }

    vector<string> files;
    if (argc == 2) {
        for (const auto &entry : filesystem::directory_iterator(argv[1])) {
            const auto &path = entry.path();
            string builder = argv[1];
            builder += '/';
            builder += path.stem().string() + path.extension().string();
            files.push_back(builder);
        }
    } else {
        std::cout << "Enter a directory to input .vox files from:\n> ";
        string dir = "";
        cin >> dir;
        try {
            for (const auto &entry : filesystem::directory_iterator(dir)) {
                const auto &path = entry.path();
                string builder = dir;
                builder += '/';
                builder += path.stem().string() + path.extension().string();
                files.push_back(builder);
            }
        } catch (const filesystem::filesystem_error& e) {
            std::cout << "Could not open file " << e.path1().generic_string() << endl;
        }
    }

    for (string filename : files) {

        fstream voxfile;
        voxfile.open(filename);
        if (voxfile.fail()) {
            std::cout << "Error opening " << filename << endl;
            continue;
        }

        if (filename.substr(filename.size() - 4, 4) != ".vox") {
            std::cout << "Error opening " << filename << endl;
            continue;
        }

        string mc_fn = "./";
        string build_temp;
        for (int i = filename.size() - 5; i >= 0; i--) {
            if (filename[i] == '/' || filename[i] == '\\') break;
            build_temp += filename[i];
        }
        for (int i = build_temp.size() - 1; i >= 0; i--) mc_fn += build_temp[i];
        mc_fn += ".mcfunction";

        remove(mc_fn.c_str());

        fstream mcfile;
        mcfile.open(mc_fn, ios::out);
        if (mcfile.fail()) {
            std::cout << "Error creating " << mc_fn << endl;
            continue;
        }

        string line;
        getline(voxfile, line);
        int height = -1;
        int ns = -1;

        mcfile << "fill ~ ~ ~ ~30 ~30 ~30 air" << endl;

        while (getline(voxfile, line)) {
            if (line.empty()) {
                height++;
                ns = -1;
                continue;
            }

            size_t end = line.size();
            // x, z, y
            ns++;
            for (size_t i = 0; i < end; i++) {
                switch (line[i]) {
                    case 'f':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        break;
                    case 'e':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " air" << endl;
                        break;
                    case 'd':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        break;
                    case 'c':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " air" << endl;
                        break;
                    case 'b':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        break;
                    case 'a':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " air" << endl;
                        break;
                    case '9':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        break;
                    case '8':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " air" << endl;
                        break;
                    case '7':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        break;
                    case '6':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " air" << endl;
                        break;
                    case '5':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        break;
                    case '4':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " air" << endl;
                        break;
                    case '3':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        break;
                    case '2':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " air" << endl;
                        break;
                    case '1':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " iron_block" << endl;
                        break;
                    case '0':
                        mcfile << "setblock ~" << 4 * i << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 1 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 2 << " ~" << height << " ~" << ns << " air" << endl;
                        mcfile << "setblock ~" << 4 * i + 3 << " ~" << height << " ~" << ns << " air" << endl;
                        break;
                }
            }
        }
        mcfile << "tellraw @a {\"text\":\"Successfully created map.\",\"color\":\"green\"}" << endl;
        std::cout << "Successfully created " << mc_fn << endl;

        voxfile.close();
        mcfile.close();
    }
}