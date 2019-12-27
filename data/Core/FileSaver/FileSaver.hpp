#ifndef DATASAVER_HPP_INCLUDED
#define DATASAVER_HPP_INCLUDED
#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <fstream>
using namespace std;

class FileSaver {
private:
    string dataPath;
    string basePath;

public:
    FileSaver(string dataPath) {
        basePath = "data/Data/";
        this->dataPath = dataPath;
    }
    void setDataPath(string dataPath) {
        this->dataPath = dataPath;
    }
    void set(vector<string> lines) {
        ofstream file;
        string finalPath = basePath + dataPath;
        file.open(finalPath.c_str(), ios::trunc);
        if (!file) {
            return;
        }
        vector<string>::iterator it;
        for (it = lines.begin(); it != lines.end(); it++) {
            file << (*it);
            file << endl;
        }
    }
};

#endif // DATASAVER_HPP_INCLUDED
