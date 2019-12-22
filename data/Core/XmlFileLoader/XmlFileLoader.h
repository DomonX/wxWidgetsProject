#ifndef XMLFILELOADER_H_INCLUDED
#define XMLFILELOADER_H_INCLUDED
#include "../XmlParser/XmlParser.hpp"
#include "../FileLoader/FileLoader.hpp"
class XmlFileLoader {
private:
    XmlParser * xml;
    FileLoader * file;
public:
    XmlFileLoader(string dataPath) {
        xml = new XmlParser();
        file = new FileLoader(dataPath);
    }
    void addSelector(string selector) {
        xml->addSelector(selector);
    }
    void clearSelectors() {
        xml->clearSelectors();
    }
    void deleteSelector(string selector) {
        xml->deleteSelector(selector);
    }
    vector<XmlParserResult *> get() {
        vector<string> lines = file->get();
        return xml->get(lines);
    }
};

#endif // XMLFILELOADER_H_INCLUDED
