#ifndef DATACOMPONENT_HPP_INCLUDED
#define DATACOMPONENT_HPP_INCLUDED

class DataComponent {
private:
    XmlFileLoader * dataLoader;
public:
    vector<XmlParserResult *> loaderResult;
    void connectData(string path) {
        dataLoader = new XmlFileLoader(path);
    }
    virtual void connectSelectors() {}
    void loadData() {
        loaderResult = dataLoader->get();
    }

};
#endif // DATACOMPONENT_HPP_INCLUDED
