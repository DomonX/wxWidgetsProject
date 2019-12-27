#ifndef TREEFILTER_HPP_INCLUDED
#define TREEFILTER_HPP_INCLUDED
class treeFilter : public VisualComponent {
public:
    Tree * treeElement;
    TextInput * textElement;

    treeFilter(wxWindow * parent, string componentID, int viewWidth) : VisualComponent(parent, componentID, viewWidth) {}

    void loadSearch() {
        textElement = new TextInput(this->ownerWindow, "Search", "");
        textElement->connect(this);
    }
    void loadTree() {
        treeElement = new Tree(this->ownerWindow, "Tree" , "Pages");
        treeElement->connect(this);
    }

    void handleEvent(Event * event) {
        if(event->eventType == "onChange" && event->path.at(0) == "Search") {
            handleSearch(event);
            deleteEvent(event);
            return;
        }
        VisualComponent::handleEvent(event);
    }
    void handleSearch(Event * event) {
        treeElement->filter(textElement->getText());
    }
};

#endif // TREEFILTER_HPP_INCLUDED
