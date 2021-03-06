#ifndef TREETEST_HPP_INCLUDED
#define TREETEST_HPP_INCLUDED
#include "../TreePageAdder/treePageAdder.hpp"
#include "../../Controls/Tree/TreeFilter.hpp"
#include "../../XMLModels/TreeItemGame.xml.hpp"
#include "../TreeGame/TreeGame.hpp"
#include "../GameFilter/gameFilter.hpp"
class treeTest : public VisualComponent {
public:
    treePageAdder * adderElement;
    gameFilter * filterElement;
    TreeFilter * treeElement;
    treeTest(wxWindow * parent, string componentID, int viewWidth): VisualComponent(parent, componentID, viewWidth) {
        prepareChildren();
        treeElement->treeElement->connectData("menu.txt");
        treeElement->treeElement->loadData();
    }
    void prepareChildren() {
        adderElement = new treePageAdder(this->ownerWindow, "add", 2);
        adderElement->connect(this);
        filterElement = new gameFilter(this->ownerWindow, "fil", 2);
        filterElement->connect(this);
        treeElement = new TreeFilter(this->ownerWindow, "tree", 1);
        treeElement->loadSearch();
        loadTreeGame();
        treeElement->connect(this);
    }
    void loadTreeGame() {
        treeElement->treeElement = new TreeGame(treeElement->ownerWindow, "Tree" , "Pages");
        treeElement->treeElement->connect(treeElement);
    }
    bool handleEvent(Event * event) {
        if(event->eventType == "onAddPage") {
            handlePageAdd(event);
            return true;
        }
        if(event->eventType == "onFilter") {
            handleFilter(event);
            return true;
        }
        return false;
    }
    void handlePageAdd(Event * event) {
        TreeItemGameXml * temp = new TreeItemGameXml();
        temp->label = adderElement->getLabel();
        temp->link = adderElement->getLink();
        temp->id = adderElement->getId();
        temp->type = adderElement->getType();
        treeElement->addItem(temp);
        treeElement->saveData();
    }
    void handleFilter(Event * event) {
        vector<string> keys;
        if(filterElement->RPG->getValue()) {
            keys.push_back("RPG");
        }
        if(filterElement->FPS->getValue()) {
            keys.push_back("FPS");
        }
        if(filterElement->MMORPG->getValue()) {
            keys.push_back("MMORPG");
        }
        if(filterElement->Race->getValue()) {
            keys.push_back("Race");
        }
        if(filterElement->Action->getValue()) {
            keys.push_back("Action");
        }
        if(filterElement->Simulation->getValue()) {
            keys.push_back("Simulation");
        }
          if(filterElement->Strategy->getValue()) {
            keys.push_back("Strategy");
        }
           if(filterElement->Sandbox->getValue()) {
            keys.push_back("Sandbox");
        }
           if(filterElement->Arcade->getValue()) {
            keys.push_back("Arcade");
        }
           if(filterElement->Survival->getValue()) {
            keys.push_back("Survival");
        }
           if(filterElement->Horror->getValue()) {
            keys.push_back("Horror");
        }
           if(filterElement->BattleRoyal->getValue()) {
            keys.push_back("BattleRoyal");
        }
        treeElement->treeElement->filter(keys);
    }
};

#endif // TREETEST_HPP_INCLUDED
