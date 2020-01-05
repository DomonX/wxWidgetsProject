#ifndef XMLFILEMANAGER_H_INCLUDED
#define XMLFILEMANAGER_H_INCLUDED
#include "../XmlParser/XmlParser.hpp"
#include "../FileLoader/FileLoader.hpp"
#include "../FileSaver/FileSaver.hpp"
#include "../XmlParser/XmlSelector.hpp"
class XmlFileManager {
private:
    XmlParser *xml;
    FileLoader *fileOut;
    FileSaver *fileIn;

public:
    XmlFileManager(string dataPath) {
        xml = new XmlParser();
        fileOut = new FileLoader(dataPath);
        fileIn = new FileSaver(dataPath);
    }
    vector<XmlParserResult *> get() {
        vector<string> lines = fileOut->get();
        return xml->load(lines);
    }
string set(vector<XmlParserResult *> lines) {
    vector<XmlParserResult *>::iterator it;
    vector<string> stringLines;
    for (it = lines.begin(); it != lines.end(); it++) {
        XmlSelector * sel = new XmlSelector((*it)->selector);
        string temp;
        temp.append(sel->beginSelector);
        if((*it)->children.empty()) {
            temp.append((*it)->data);
        } else {
            temp.append(set((*it)->children));
        }
        temp.append(sel->endSelector);
        stringLines.push_back(temp);
    }
    fileIn->set(stringLines);
    return xml->flattenLines(stringLines);
}
};

#endif // XMLFILEMANAGER_H_INCLUDED
