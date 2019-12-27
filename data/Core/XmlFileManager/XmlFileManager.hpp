#ifndef XMLFILEMANAGER_H_INCLUDED
#define XMLFILEMANAGER_H_INCLUDED
#include "../XmlParser/XmlParser.hpp"
#include "../FileLoader/FileLoader.hpp"
#include "../FileSaver/FileSaver.hpp"
class XmlFileManager {
private:
    XmlParser *xml;
    FileLoader *file;
    FileSaver *fileS;

public:
    XmlFileManager(string dataPath) {
        xml = new XmlParser();
        file = new FileLoader(dataPath);
        fileS = new FileSaver(dataPath);
    }
    vector<XmlParserResult *> get() {
        vector<string> lines = file->get();
        return xml->load(lines);
    }
    void set(vector<XmlParserResult *> lines) {
        vector<XmlParserResult *>::iterator it;
        vector<string> stringLines;
        for (it = lines.begin(); it != lines.end(); it++) {
            string temp;
            temp.append("<" + (*it)->selector + ">");
            temp.append((*it)->data);
            temp.append("</" + (*it)->selector + ">");
            stringLines.push_back(temp);
        }
        fileS->set(stringLines);
    }
};

#endif // XMLFILEMANAGER_H_INCLUDED
