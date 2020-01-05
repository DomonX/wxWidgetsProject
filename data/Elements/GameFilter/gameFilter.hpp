#ifndef GAMEFILTER_HPP_INCLUDED
#define GAMEFILTER_HPP_INCLUDED
#include "../../Controls/CheckBox/checkbox.hpp"
class gameFilter: public VisualComponent{
protected:
    void prepareChildren() {
        RPG = new Checkbox(this->ownerWindow, "RPG", "RPG");
        RPG->connect(this);
        FPS = new Checkbox(this->ownerWindow, "FPS", "FPS");
        FPS->connect(this);
        MMORPG = new Checkbox(this->ownerWindow, "MMORPG", "MMORPG");
        MMORPG->connect(this);
        Race = new Checkbox(this->ownerWindow, "Race", "Race");
        Race->connect(this);
        Action = new Checkbox(this->ownerWindow, "Action", "Action");
        Action->connect(this);
        Simulation = new Checkbox(this->ownerWindow, "Simulation", "Simulation");
        Simulation->connect(this);
        Strategy = new Checkbox(this->ownerWindow, "Strategy", "Strategy");
        Strategy->connect(this);
        Other = new Checkbox(this->ownerWindow, "Other", "Other");
        Other->connect(this);
        Submit = new Button(this->ownerWindow, "Submit", "Filtruj");
        Submit->connect(this);
    }
    void handleEvent(Event * event) {
        if(event->eventType == "onClick" && event->path.at(0) == "Submit") {
            sendFilter(event);
            deleteEvent(event);
            return;
        }
        VisualComponent::handleEvent(event);
    }
    void sendFilter(Event * event) {
        Event * ev = new Event("onFilter", event->caller);
        VisualComponent::handleEvent(ev);
    }
public:
    Checkbox * RPG;
    Checkbox * FPS;
    Checkbox * MMORPG;
    Checkbox * Race;
    Checkbox * Action;
    Checkbox * Simulation;
    Checkbox * Strategy;
    Checkbox * Other;
    Button * Submit;
    gameFilter(wxWindow * parent, string componentID, int viewWidth) : VisualComponent(parent, componentID, viewWidth) {
        prepareChildren();
    }
};

#endif // GAMEFILTER_HPP_INCLUDED
