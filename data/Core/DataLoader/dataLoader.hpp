#ifndef DATALOADER_HPP_INCLUDED
#define DATALOADER_HPP_INCLUDED
#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <fstream>
using namespace std;

class dataLoaderSelector {
public:
    string baseSelector;
    string beginSelector;
    string endSelector;

    dataLoaderSelector(string baseSelector) {
        this->baseSelector = baseSelector;
        beginSelector = "<" + baseSelector + ">";
        endSelector = "</" + baseSelector + ">";
    }
};

class dataLoaderResult {
    public:
    string selector;
    string data;
    dataLoaderResult(string selector, string data) {
        this->selector = selector;
        this->data = data;
    }
};

class dataLoader {
private:
        string dataPath;
        const string basePath = "data/Data/";
        vector<dataLoaderResult *> result;
        bool isInside;
        dataLoaderSelector * currentSelector;
public:
    dataLoader(string dataPath) {
        this->dataPath = dataPath;
    }
    vector<dataLoaderResult *> getData(vector<string> selectors) {
        result.empty();
        isInside = false;
        currentSelector = NULL;
        ifstream file;
        vector<dataLoaderSelector *> selVec = getVectorOfSelectors(selectors);
        string watch;
        try{
            watch = selVec.at(1)->baseSelector;
        } catch(exception e) {
            watch = "";
        }
        vector<dataLoaderSelector *>::iterator it_sel;
        string finalPath = basePath + dataPath;
        file.open(finalPath.c_str(), ios::out);
        if(!file) {
            return result;
        }
        string buffer;
        string finalBuffer;
        while(getline(file, buffer)) {
            lookForBeginSelector(&buffer, selVec);
            lookForEndSelector(&buffer, &finalBuffer, selVec);
            if(isInside) {
                finalBuffer += buffer;
            }
        }
        return result;
    }

    void lookForBeginSelector(string * buffer, vector<dataLoaderSelector *> selectors) {
        if(isInside) {
            return;
        }
        string watch = (*buffer);
        vector<dataLoaderSelector *>::iterator it;
        for(it = selectors.begin(); it != selectors.end(); it++) {
            if((*buffer).find((*it)->beginSelector) == std::string::npos) {
                continue;
            }
            (*buffer) = eraseSubStr((*buffer),(*it)->beginSelector);
            currentSelector = (*it);
            isInside = true;
            return;
        }
    }

    void lookForEndSelector(string * buffer, string * finalBuffer, vector<dataLoaderSelector *> selectors) {
        if(!isInside) {
            return;
        }
        if((*buffer).find(currentSelector->endSelector) != std::string::npos) {
            (*buffer) = eraseSubStr((*buffer),currentSelector->endSelector);
            (*finalBuffer) += (*buffer);
            result.push_back(new dataLoaderResult(currentSelector->baseSelector,(*finalBuffer)));
            (*finalBuffer) = "";
            isInside = false;
        }
    }

    vector<dataLoaderSelector *> getVectorOfSelectors(vector<string> selectors) {
        vector<dataLoaderSelector *> result;
        vector<string>::iterator it;
        for(it = selectors.begin(); it != selectors.end(); it++) {
            result.push_back(new dataLoaderSelector(*it));
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
