#ifndef TREETEST_HPP_INCLUDED
#define TREETEST_HPP_INCLUDED
#include "../TreePageAdder/treePageAdder.hpp"
#include "../../Controls/Tree/TreeFilter.hpp"
#include "../../XMLModels/TreeItemGame.xml.hpp"
#include "../TreeGame/TreeGame.hpp"
class treeTest : public VisualComponent {
public:
    treePageAdder * adderElement;
    treeFilter * treeElement;
    treeTest(wxWindow * parent, string componentID, int viewWidth): VisualComponent(parent, componentID, viewWidth) {
        prepareChildren();
        treeElement->treeElement->connectData("menu.txt");
        treeElement->treeElement->loadData();
    }
    void prepareChildren() {
        adderElement = new treePageAdder(this->ownerWindow, "add", 2);
        adderElement->connect(this);
        treeElement = new treeFilter(this->ownerWindow, "tree", 1);
        treeElement->loadSearch();
        loadTreeGame();
        treeElement->connect(this);
    }
    void loadTreeGame() {
        treeElement->treeElement = new TreeGame(treeElement->ownerWindow, "Tree" , "Pages");
        treeElement->treeElement->connect(treeElement);
    }
    void handleEvent(Event * event) {
        if(event->eventType == "onAddPage") {
            handlePageAdd(event);
        }
        VisualComponent::handleEvent(event);
    }
    void handlePageAdd(Event * event) {
        TreeItemGameXml * temp = new TreeItemGameXml();
        temp->label = adderElement->getLabel();
        temp->link = adderElement->getLink();
        temp->id = adderElement->getId();
        temp->type = adderElement->getType();
        treeElement->treeElement->addItem(temp);
        treeElement->treeElement->saveData();
    }
    virtual TreeItemBaseXml * buildTreeItem(XmlParserResult * result) {
        return new TreeItemGameXml(result);
    }

};

#endif // TREETEST_HPP_INCLUDED
