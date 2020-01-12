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
        Sandbox = new Checkbox(this->ownerWindow, "Sandbox", "Sandbox");
        Sandbox->connect(this);
        BattleRoyal = new Checkbox(this->ownerWindow, "BattleRoyal", "BattleRoyal");
        BattleRoyal->connect(this);
        Horror = new Checkbox(this->ownerWindow, "Horror", "Horror");
        Horror->connect(this);
        Survival = new Checkbox(this->ownerWindow, "Survival", "Survival");
        Survival->connect(this);
        Arcade = new Checkbox(this->ownerWindow, "Arcade", "Arcade");
        Arcade->connect(this);
        Submit = new Button(this->ownerWindow, "Submit", "Filtruj");
        Submit->connect(this);
    }
    bool handleEvent(Event * event) {
        if(event->eventType == "onClick" && event->path.at(0) == "Submit") {
            sendFilter(event);
            return true;
        }
        return false;
    }
    void sendFilter(Event * event) {
        Event * ev = new Event("onFilter", event->caller);
        processEvent(ev);
    }
public:
    Checkbox * RPG;
    Checkbox * Sandbox;
    Checkbox * Arcade;
    Checkbox * Survival;
    Checkbox * Horror;
    Checkbox * BattleRoyal;
    Checkbox * FPS;
    Checkbox * MMORPG;
    Checkbox * Race;
    Checkbox * Action;
    Checkbox * Simulation;
    Checkbox * Strategy;
    Button * Submit;
    gameFilter(wxWindow * parent, string componentID, int viewWidth) : VisualComponent(parent, componentID, viewWidth) {
        prepareChildren();
    }
};

#endif // GAMEFILTER_HPP_INCLUDED
