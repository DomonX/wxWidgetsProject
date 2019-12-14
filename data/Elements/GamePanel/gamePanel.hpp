#ifndef GAMEPANEL_HPP_INCLUDED
#define GAMEPANEL_HPP_INCLUDED
#include "../../Core/Component/panelComponent.hpp"
#include "../../Core/DataLoader/dataLoader.hpp"
class GamePanel : public PanelComponent{
private:
    dataLoader * dataLd;
public:
    GamePanel(wxWindow * parent, string componentID) : PanelComponent(parent, componentID) {
        prepareChildren();
    }
    void handleEvent(Event * event) {
        PanelComponent::handleEvent(event);
    }
    void prepareChildren() {}
    void connectData(string path) {
        dataLd = new dataLoader(path);
    }
    void loadData() {
        vector<string> result = dataLd->getData("label");
        vector<string>::iterator it;
        for(it = result.begin(); it != result.end(); it++) {
            Label * lb = new Label(this->elementRef,*it,*it);
            lb->connect(this);
        }
    }
};

#endif // GAMEPANEL_HPP_INCLUDED
