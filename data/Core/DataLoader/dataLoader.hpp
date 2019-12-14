#ifndef DATALOADER_HPP_INCLUDED
#define DATALOADER_HPP_INCLUDED
#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <fstream>
using namespace std;
class dataLoader {
private:
        string dataPath;
        const string basePath = "data/Data/";
public:
    dataLoader(string dataPath) {
        this->dataPath = dataPath;
    }
    vector<string> getData(string selector) {
        vector<string> result;
        ifstream file;
        string finalPath = basePath + dataPath;
        string beginSelector = "<" + selector + ">";
        string endSelector = "</" + selector + ">";
        file.open(finalPath.c_str(), ios::out);
        if(!file) {
            return result;
        }
        string buffer;
        string finalBuffer;
        bool isInside;
        while(getline(file, buffer)) {
            if(buffer.find(beginSelector) != std::string::npos) {
                buffer = eraseSubStr(buffer,beginSelector);
                isInside = true;
            }
            if(buffer.find(endSelector) != std::string::npos) {
                buffer = eraseSubStr(buffer,endSelector);
                finalBuffer += buffer;
                result.push_back(finalBuffer);
                finalBuffer = "";
                isInside = false;
            }
            if(isInside) {
                finalBuffer += buffer;
            }
        }
        return result;
    }
    string eraseSubStr(string src, string eraser) {
        size_t pos = src.find(eraser);
        if (pos != std::string::npos){
            src.erase(pos, eraser.length());
        }
        return src;
    }
};

#endif // DATALOADER_HPP_INCLUDED
