#ifndef DATACOMPONENT_HPP_INCLUDED
#define DATACOMPONENT_HPP_INCLUDED
using namespace std;
class DataComponent {
private:
    void renderComponent() {
        vector<XmlParserResult *>::iterator it;
        for (it = loaderResult.begin(); it != loaderResult.end(); it++) {
            renderControl((*it));
        }
    }
protected:
    virtual void connectSelectors() {}
    virtual void beforeRender() {}
    virtual void afterRender() {}
    virtual void renderControl(XmlParserResult *xml) {}
    virtual vector<XmlParserResult *> prepareDataToSave() {
        vector<XmlParserResult *> temp;
        return temp;
    }
    XmlFileManager *dataLoader;
    vector<XmlParserResult *> loaderResult;
public:
    void render() {
        beforeRender();
        renderComponent();
        afterRender();
    }
    void connectData(string path) {
        dataLoader = new XmlFileManager(path);
        connectSelectors();
    }
    void loadData() {
        loaderResult.empty();
        this->loaderResult = dataLoader->get();
        this->render();
    }
    void saveData() {
        dataLoader->set(prepareDataToSave());
    }
};
#endif // DATACOMPONENT_HPP_INCLUDED
