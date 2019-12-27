#ifndef XMLPARSER_HPP_INCLUDED
#define XMLPARSER_HPP_INCLUDED

#include <vector>
#include "XmlParserResult.hpp"
#include "XmlSelector.hpp"

using namespace std;

class XmlParser {
private:
    vector<XmlParserResult *> result;
    string eraseSelectorSubString(string src, string selector) {
        size_t pos = src.find(selector);
        if (pos != std::string::npos){
            src.erase(pos, selector.length());
        }
        return src;
    }
    string flattenLines(vector<string> lines) {
        vector<string>::iterator it;
        string result;
        for(it = lines.begin(); it != lines.end(); it++) {
            result.append((*it));
            result.append(" ");
        }
    }
public:
    vector<XmlParserResult *> load(vector<string> lines) {
        vector<string>::iterator it;
    }
};

#endif // XMLPARSER_HPP_INCLUDED
