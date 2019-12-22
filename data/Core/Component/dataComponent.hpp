#ifndef DATACOMPONENT_HPP_INCLUDED
#define DATACOMPONENT_HPP_INCLUDED
using namespace std;
class DataComponent {
public:
    XmlFileLoader * dataLoader;
    vector<XmlParserResult *> loaderResult;
    virtual void connectSelectors() {}
    virtual void render() {}
    void connectData(string path) {
        dataLoader = new XmlFileLoader(path);
        connectSelectors();
    }
    void loadData() {
        loaderResult.empty();
        this->loaderResult = dataLoader->get();
        this->render();
    }
};
#endif // DATACOMPONENT_HPP_INCLUDED
