#ifndef TREEFILTER_HPP_INCLUDED
#define TREEFILTER_HPP_INCLUDED
class treeFilter : public VisualComponent {
protected:
    bool handleEvent(Event * event) {
        if(event->eventType == "onChange") {
            handleOnChange(event);
            deleteEvent(event);
            return true;
        }
        return false;
    }
    void handleOnChange(Event * event) {
        if(event->path.at(0) == "Search") {
            handleSearch(event);
        }
    }
    void handleSearch(Event * event) {
        search(textElement->getText());
    }
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

    void addItem(TreeItemBaseXml * newItem) {
        treeElement->addItem(newItem);
    }

    void search(string key) {
        treeElement->search(key);
    }

    string getSelectedItemID() {
        return treeElement->getSelectedItemID();
    }
    void saveData() {
        treeElement->saveData();
    }

};

#endif // TREEFILTER_HPP_INCLUDED
