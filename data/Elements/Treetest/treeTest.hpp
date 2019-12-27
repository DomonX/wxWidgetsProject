#ifndef TREETEST_HPP_INCLUDED
#define TREETEST_HPP_INCLUDED
#include "../TreePageAdder/treePageAdder.hpp"
#include "../../Controls/Tree/TreeFilter.hpp"
class treeTest : public VisualComponent {
public:
    treePageAdder * adderElement;
    treeFilter * treeElement;
    treeTest(wxWindow * parent, string componentID, int viewWidth): VisualComponent(parent, componentID, viewWidth) {
        prepareChildren();
        treeElement->treeElement->connectData("data.txt");
        treeElement->treeElement->loadData();
    }
    void prepareChildren() {
        adderElement = new treePageAdder(this->ownerWindow, "add", 1);
        adderElement->connect(this);
        treeElement = new treeFilter(this->ownerWindow, "tree", 1);
        treeElement->connect(this);
    }
    void handleEvent(Event * event) {
        if(event->eventType == "onAddPage") {
            handlePageAdd(event);
        }
        VisualComponent::handleEvent(event);
    }
    void handlePageAdd(Event * event) {
        string text = adderElement->textElement->getText();
        treeElement->treeElement->addItem(text, text);
        treeElement->treeElement->saveData();
    }
};

#endif // TREETEST_HPP_INCLUDED
