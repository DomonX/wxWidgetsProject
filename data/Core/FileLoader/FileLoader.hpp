#ifndef DATALOADER_HPP_INCLUDED
#define DATALOADER_HPP_INCLUDED
#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <fstream>
using namespace std;

class FileLoader {
private:
        string dataPath;
        string basePath;
public:
    FileLoader(string dataPath) {
        basePath = "data/Data/";
        this->dataPath = dataPath;
    }
    void setDataPath(string dataPath) {
        this->dataPath = dataPath;
    }
    vector<string> get() {
        ifstream file;
        string finalPath = basePath + dataPath;
        file.open(finalPath.c_str(), ios::out);
        vector<string> result;
        if(!file) {
            return result;
        }
        string buffer;
        while(getline(file, buffer)) {
            result.push_back(buffer);
        }
        return result;
    }
};

#endif // DATALOADER_HPP_INCLUDED
