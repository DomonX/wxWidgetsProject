#ifndef XMLPARSER_HPP_INCLUDED
#define XMLPARSER_HPP_INCLUDED

#include <vector>
#include "XmlParserResult.hpp"
#include "XmlSelector.hpp"

using namespace std;

class XmlParser {
private:
    vector<XmlParserResult *> result;
    string flattenLines(vector<string> lines) {
        vector<string>::iterator it;
        string result;
        for(it = lines.begin(); it != lines.end(); it++) {
            result.append((*it));
            result.append(" ");
        }
        return result;
    }
    vector<XmlParserResult *> loadFlat(string line) {
        vector<XmlParserResult *> result;
        string buffer = line;
        while(true){
            size_t startingPosition = buffer.find("<");
            if(startingPosition == std::string::npos) {
                return result;
            }
            size_t endingPosition = buffer.find(">");
            if(endingPosition == std::string::npos) {
                return result;
            }
            if(startingPosition+1 > endingPosition -1) {
                return result;
            }
            int newStrLen = endingPosition - startingPosition - 1;
            string currentSelector = buffer.substr(startingPosition+1, newStrLen);
            string endSelector = "</" + currentSelector + ">";
            size_t endOfTag = buffer.find(endSelector);
            if(endOfTag == std::string::npos) {
                return result;
            }
            int startOfInside = endingPosition + 1;
            int insideLen = endOfTag - startOfInside;
            string inside = buffer.substr(startOfInside,insideLen);
            vector<XmlParserResult *> children = loadFlat(inside);
            XmlParserResult * temp = new XmlParserResult(currentSelector, inside);
            temp->children = children;
            buffer = buffer.substr(endOfTag + endSelector.length(), buffer.length()-1);
            result.push_back(temp);
        }
        return result;
    }

public:
    vector<XmlParserResult *> load(vector<string> lines) {
        string flattenContent = flattenLines(lines);
        return loadFlat(flattenContent);
    }
};

#endif // XMLPARSER_HPP_INCLUDED
