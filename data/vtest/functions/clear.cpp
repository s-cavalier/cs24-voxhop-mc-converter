#include <filesystem>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
    vector<string> files;
    for (const auto &entry : filesystem::directory_iterator(".")) {
        const auto &path = entry.path();
        if (path.extension().string() != ".mcfunction") continue;
        if (path.stem().string()[0] == '_') continue;
        string builder = "./";
        builder += path.stem().string() + path.extension().string();
        files.push_back(builder);
    }

    for (string fn : files) {
        remove(fn.c_str());
        cout << "Removed " << fn << endl;
    }
}