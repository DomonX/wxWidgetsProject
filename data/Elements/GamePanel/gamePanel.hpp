#ifndef GAMEPANEL_HPP_INCLUDED
#define GAMEPANEL_HPP_INCLUDED
#include "../../Core/Component/panelComponent.hpp"
#include "../../Core/XmlFileLoader/XmlFileLoader.h"
#include "../../Controls/Image/Image.hpp"
#include "../../Core/Component/dataComponent.hpp"
class GamePanel : public PanelComponent {
private:
    XmlFileLoader * dataLd;
public:
    GamePanel(wxWindow * parent, string componentID) : PanelComponent(parent, componentID) {
        prepareChildren();
    }
    void handleEvent(Event * event) {
        PanelComponent::handleEvent(event);
    }
    void prepareChildren() {}
    void connectData(string path) {
        dataLd = new XmlFileLoader(path);
        dataLd->addSelector("label");
        dataLd->addSelector("img");

    }
    void loadData() {
        vector<XmlParserResult *> result = dataLd->get();
        vector<XmlParserResult *>::iterator it;
        for(it = result.begin(); it != result.end(); it++) {
            if((*it)->selector == "label") {
                addText((*it)->data);
            }
            if((*it)->selector == "img") {
                addImg((*it)->data);
            }
        }
    }
    void addText(string label) {
        LabelMetaData * labelMD = new LabelMetaData();;
        labelMD->componentID = label;
        labelMD->label = label;
        labelMD->parent = this->elementRef;
        labelMD->width = 900;
        labelMD->height = -1;
        Label * lb = new Label(labelMD);
        lb->connect(this);
    }
    void addImg(string path) {
        Image * img = new Image(this->elementRef,path,path);
        img->connect(this);
    }
};

#endif // GAMEPANEL_HPP_INCLUDED
