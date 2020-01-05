#ifndef TREEPAGEADDER_HPP_INCLUDED
#define TREEPAGEADDER_HPP_INCLUDED

class treePageAdder : public VisualComponent {
public:
    treePageAdder(wxWindow * parent, string componentID, int viewWidth) : VisualComponent(parent, componentID, viewWidth) {
        prepareChildren();
    }
TextInput * label;
TextInput * id;
TextInput * link;
TextInput * type;
Button * buttonElement;
void prepareChildren() {
    addLabelForControl("Label", "labelForLabel");
    label = new TextInput(this->ownerWindow, "Label", "");
    label->connect(this);
    addLabelForControl("ID", "labelForLabel");
    id = new TextInput(this->ownerWindow, "ID", "");
    id->connect(this);
    addLabelForControl("Link do pliku", "labelForLabel");
    link = new TextInput(this->ownerWindow, "Link", "");
    link->connect(this);
    addLabelForControl("Typ", "labelForType");
    type = new TextInput(this->ownerWindow, "Type", "");
    type->connect(this);
    buttonElement = new Button(this->ownerWindow, "Submit", "Add Page");
    buttonElement->connect(this);
}
void addLabelForControl(string label, string id) {
    LabelMetaData * lbMD = new LabelMetaData();
    lbMD->componentID = id;
    lbMD->height = 15;
    lbMD->width = -1;
    lbMD->parent = this->ownerWindow;
    lbMD->label = label;
    Label * labelL = new Label(lbMD);
    labelL->connect(this);
}
    bool handleEvent(Event * event) {
        if(event->eventType == "onClick" && event->path.at(0) == "Submit") {
            sendAddPage(event);
            return true;
        }
        return false;
    }
    void sendAddPage(Event * event) {
        Event * ev = new Event("onAddPage", event->caller);
        processEvent(ev);
    }
    string getLabel() {
        return label->getText();
    }
    string getId() {
        return id->getText();
    }
    string getLink() {
        return link->getText();
    }
    string getType() {
        return type->getText();
    }

};

#endif // TREEPAGEADDER_HPP_INCLUDED
