#ifndef XMLPARSER_HPP_INCLUDED
#define XMLPARSER_HPP_INCLUDED

#include <vector>
#include "XmlParserResult.hpp"
#include "XmlSelector.hpp"

using namespace std;

class XmlParser {
private:
    vector<XmlParserResult *> loadFlat(string line) {
        vector<XmlParserResult *> result;
        string buffer = line;
        while(true){
            size_t startSelectorBegin = buffer.find("<");
            if(startSelectorBegin == std::string::npos) {
                return result;
            }
            size_t startSelectorEnd = buffer.find(">");
            if(startSelectorEnd == std::string::npos) {
                return result;
            }
            if(startSelectorBegin+1 > startSelectorEnd -1) {
                return result;
            }
            int startSelectorLen = startSelectorEnd - startSelectorBegin - 1;
            XmlSelector * sel = new XmlSelector(buffer.substr(startSelectorBegin+1, startSelectorLen));
            size_t endSelectorBegin = buffer.find(sel->endSelector);
            if(endSelectorBegin == std::string::npos) {
                return result;
            }
            size_t startOfInside = startSelectorEnd + 1;
            int insideLen = endSelectorBegin - startOfInside;
            string inside = buffer.substr(startOfInside,insideLen);
            vector<XmlParserResult *> children = loadFlat(inside);
            XmlParserResult * temp = new XmlParserResult(sel->baseSelector, inside);
            temp->children = children;
            buffer = buffer.substr(endSelectorBegin + sel->endSelector.length(), buffer.length()-1);
            result.push_back(temp);
            free(sel);
        }
        return result;
    }

public:
    vector<XmlParserResult *> load(vector<string> lines) {
        string flattenContent = flattenLines(lines);
        return loadFlat(flattenContent);
    }
    string flattenLines(vector<string> lines) {
        vector<string>::iterator it;
        string result;
        for(it = lines.begin(); it != lines.end(); it++) {
            result.append((*it));
            result.append(" ");
        }
        return result;
    }
};

#endif // XMLPARSER_HPP_INCLUDED
