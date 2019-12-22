#ifndef GAMEPANEL_HPP_INCLUDED
#define GAMEPANEL_HPP_INCLUDED
#include "../../Core/Component/panelComponent.hpp"
#include "../../Core/XmlFileLoader/XmlFileLoader.h"
#include "../../Controls/Image/Image.hpp"
#include "../../Core/Component/dataComponent.hpp"
class GamePanel : public PanelComponent, public DataComponent {
public:
    GamePanel(wxWindow * parent, string componentID) : PanelComponent(parent, componentID), DataComponent() {}
    void handleEvent(Event * event) {
        PanelComponent::handleEvent(event);
    }
    void connectSelectors() {
        dataLoader->addSelector("label");
        dataLoader->addSelector("img");
    }
    void renderControl(XmlParserResult * result) {
        if(result->selector == "label") {
            addText(result->data);
        }
        if(result->selector == "img") {
            addImg(result->data);
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
