#ifndef XMLPARSER_HPP_INCLUDED
#define XMLPARSER_HPP_INCLUDED

#include <vector>
#include "XmlParserResult.hpp"
#include "XmlSelector.hpp"

using namespace std;

class XmlParser {
private:
    vector<XmlSelector *> selectors;
    vector<XmlParserResult *> result;
    vector<string> linesBuffer;
    string currentLine;
    string contentBuffer;
    XmlSelector * currentSelector;
    bool isInside;
    void resetParser() {
        result.empty();
        linesBuffer.empty();
        contentBuffer = "";
        currentLine = "";
        isInside = false;
        currentSelector = NULL;
    }
    string eraseBeginSelector() {
        return eraseSelectorSubString(currentLine, currentSelector->beginSelector);
    }
    string eraseEndSelector() {
        return eraseSelectorSubString(currentLine, currentSelector->endSelector);
    }
    string eraseSelectorSubString(string src, string selector) {
        size_t pos = src.find(selector);
        if (pos != std::string::npos){
            src.erase(pos, selector.length());
        }
        return src;
    }
    void lookForBeginSelector() {
        if(isInside) {
            return;
        }
        vector<XmlSelector *>::iterator it;
        for(it = selectors.begin(); it != selectors.end(); it++) {
            if(currentLine.find((*it)->beginSelector) == std::string::npos) {
                continue;
            }
            currentSelector = (*it);
            eraseBeginSelector();
            isInside = true;
            return;
        }
    }
    void lookForEndSelector() {
        if(!isInside) {
            return;
        }
        if((currentLine.find(currentSelector->endSelector) != std::string::npos)) {
            eraseEndSelector();
            addResult();
        }
    }
    void endLine() {
        if(isInside) {
            contentBuffer += currentLine;
        }
    }
    void addResult() {
        contentBuffer += currentLine;
        result.push_back(new XmlParserResult(currentSelector->baseSelector, contentBuffer));
        contentBuffer = "";
        isInside = false;
    }
public:
    void addSelector(string selector) {
        selectors.push_back(new XmlSelector(selector));
    }
    void clearSelectors() {
        selectors.empty();
    }
    void deleteSelector(string selector) {

    }
    vector<XmlParserResult *> get(vector<string> lines) {
        resetParser();
        vector<string>::iterator it;
        for(it = linesBuffer.begin(); it != linesBuffer.end(); it++) {
            currentLine = (*it);
            lookForBeginSelector();
            lookForEndSelector();
            endLine();
        }
        return result;
    }
};

#endif // XMLPARSER_HPP_INCLUDED
