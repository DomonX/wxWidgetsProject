#ifndef DATACOMPONENT_HPP_INCLUDED
#define DATACOMPONENT_HPP_INCLUDED
using namespace std;
class DataComponent {
public:
    XmlFileManager *dataLoader;
    vector<XmlParserResult *> loaderResult;
    virtual void connectSelectors() {}
    void render() {
        beforeRender();
        renderComponent();
        afterRender();
    }
    virtual void beforeRender() {}
    virtual void afterRender() {}
    void renderComponent() {
        vector<XmlParserResult *>::iterator it;
        for (it = loaderResult.begin(); it != loaderResult.end(); it++) {
            renderControl((*it));
        }
    }
    virtual void renderControl(XmlParserResult *xml) {}
    void connectData(string path) {
        dataLoader = new XmlFileManager(path);
        connectSelectors();
    }
    void loadData() {
        loaderResult.empty();
        this->loaderResult = dataLoader->get();
        this->render();
    }
    virtual vector<XmlParserResult *> prepareDataToSave() {
        vector<XmlParserResult *> temp;
        temp.empty();
        return temp;
    }
    void saveData() {
        dataLoader->set(prepareDataToSave());
    }
};
#endif // DATACOMPONENT_HPP_INCLUDED
